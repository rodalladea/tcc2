/*M///////////////////////////////////////////////////////////////////////////////////////
 //
 //  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
 //
 //  By downloading, copying, installing or using the software you agree to this license.
 //  If you do not agree to this license, do not download, install,
 //  copy or use the software.
 //
 //
 //                           License Agreement
 //                For Open Source Computer Vision Library
 //
 // Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
 // Copyright (C) 2009, Willow Garage Inc., all rights reserved.
 // Third party copyrights are property of their respective owners.
 //
 // Redistribution and use in source and binary forms, with or without modification,
 // are permitted provided that the following conditions are met:
 //
 //   * Redistribution's of source code must retain the above copyright notice,
 //     this list of conditions and the following disclaimer.
 //
 //   * Redistribution's in binary form must reproduce the above copyright notice,
 //     this list of conditions and the following disclaimer in the documentation
 //     and/or other materials provided with the distribution.
 //
 //   * The name of the copyright holders may not be used to endorse or promote products
 //     derived from this software without specific prior written permission.
 //
 // This software is provided by the copyright holders and contributors "as is" and
 // any express or implied warranties, including, but not limited to, the implied
 // warranties of merchantability and fitness for a particular purpose are disclaimed.
 // In no event shall the Intel Corporation or contributors be liable for any direct,
 // indirect, incidental, special, exemplary, or consequential damages
 // (including, but not limited to, procurement of substitute goods or services;
 // loss of use, data, or profits; or business interruption) however caused
 // and on any theory of liability, whether in contract, strict liability,
 // or tort (including negligence or otherwise) arising in any way out of
 // the use of this software, even if advised of the possibility of such damage.
 //
 //M*/

#include "precomp.hpp"
#include "epnp.h"
#include "p3p.h"
#include <iostream>
using namespace cv;

bool cv::solvePnP( InputArray _opoints, InputArray _ipoints,
                  InputArray _cameraMatrix, InputArray _distCoeffs,
                  OutputArray _rvec, OutputArray _tvec, bool useExtrinsicGuess, int flags )
{
    Mat opoints = _opoints.getMat(), ipoints = _ipoints.getMat();
    int npoints = std::max(opoints.checkVector(3, CV_32F), opoints.checkVector(3, CV_64F));
    CV_Assert( npoints >= 0 && npoints == std::max(ipoints.checkVector(2, CV_32F), ipoints.checkVector(2, CV_64F)) );
    _rvec.create(3, 1, CV_64F);
    _tvec.create(3, 1, CV_64F);
    Mat cameraMatrix = _cameraMatrix.getMat(), distCoeffs = _distCoeffs.getMat();

    if (flags == CV_EPNP)
    {
        cv::Mat undistortedPoints;
        cv::undistortPoints(ipoints, undistortedPoints, cameraMatrix, distCoeffs);
        epnp PnP(cameraMatrix, opoints, undistortedPoints);

        cv::Mat R, rvec = _rvec.getMat(), tvec = _tvec.getMat();
        PnP.compute_pose(R, tvec);
        cv::Rodrigues(R, rvec);
        return true;
    }
    else if (flags == CV_P3P)
    {
        CV_Assert( npoints == 4);
        cv::Mat undistortedPoints;
        cv::undistortPoints(ipoints, undistortedPoints, cameraMatrix, distCoeffs);
        p3p P3Psolver(cameraMatrix);

        cv::Mat R, rvec = _rvec.getMat(), tvec = _tvec.getMat();
        bool result = P3Psolver.solve(R, tvec, opoints, undistortedPoints);
        if (result)
            cv::Rodrigues(R, rvec);
        return result;
    }
    else if (flags == CV_ITERATIVE)
    {
        CvMat c_objectPoints = opoints, c_imagePoints = ipoints;
        CvMat c_cameraMatrix = cameraMatrix, c_distCoeffs = distCoeffs;
        CvMat c_rvec = _rvec.getMat(), c_tvec = _tvec.getMat();
        cvFindExtrinsicCameraParams2(&c_objectPoints, &c_imagePoints, &c_cameraMatrix,
                                     c_distCoeffs.rows*c_distCoeffs.cols ? &c_distCoeffs : 0,
                                     &c_rvec, &c_tvec, useExtrinsicGuess );
        return true;
    }
    else
        CV_Error(CV_StsBadArg, "The flags argument must be one of CV_ITERATIVE or CV_EPNP");
    return false;
}

namespace cv
{
    namespace pnpransac
    {
        const int MIN_POINTS_COUNT = 4;

        static void project3dPoints(const Mat& points, const Mat& rvec, const Mat& tvec, Mat& modif_points)
        {
            modif_points.create(1, points.cols, CV_32FC3);
            Mat R(3, 3, CV_64FC1);
            Rodrigues(rvec, R);
            Mat transformation(3, 4, CV_64F);
            Mat r = transformation.colRange(0, 3);
            R.copyTo(r);
            Mat t = transformation.colRange(3, 4);
            tvec.copyTo(t);
            transform(points, modif_points, transformation);
        }

        struct CameraParameters
        {
            void init(Mat _intrinsics, Mat _distCoeffs)
            {
                _intrinsics.copyTo(intrinsics);
                _distCoeffs.copyTo(distortion);
            }

            Mat intrinsics;
            Mat distortion;
        };

        struct Parameters
        {
            int iterationsCount;
            float reprojectionError;
            int minInliersCount;
            bool useExtrinsicGuess;
            int flags;
            CameraParameters camera;
        };

        static void pnpTask(const vector<char>& pointsMask, const Mat& objectPoints, const Mat& imagePoints,
                     const Parameters& params, vector<int>& inliers, Mat& rvec, Mat& tvec,
                     const Mat& rvecInit, const Mat& tvecInit, Mutex& resultsMutex)
        {
            Mat modelObjectPoints(1, MIN_POINTS_COUNT, CV_32FC3), modelImagePoints(1, MIN_POINTS_COUNT, CV_32FC2);
            for (int i = 0, colIndex = 0; i < (int)pointsMask.size(); i++)
            {
                if (pointsMask[i])
                {
                    Mat colModelImagePoints = modelImagePoints(Rect(colIndex, 0, 1, 1));
                    imagePoints.col(i).copyTo(colModelImagePoints);
                    Mat colModelObjectPoints = modelObjectPoints(Rect(colIndex, 0, 1, 1));
                    objectPoints.col(i).copyTo(colModelObjectPoints);
                    colIndex = colIndex+1;
                }
            }

            //filter same 3d points, hang in solvePnP
            double eps = 1e-10;
            int num_same_points = 0;
            for (int i = 0; i < MIN_POINTS_COUNT; i++)
                for (int j = i + 1; j < MIN_POINTS_COUNT; j++)
                {
                    if (norm(modelObjectPoints.at<Vec3f>(0, i) - modelObjectPoints.at<Vec3f>(0, j)) < eps)
                        num_same_points++;
                }
            if (num_same_points > 0)
                return;

            Mat localRvec, localTvec;
            rvecInit.copyTo(localRvec);
            tvecInit.copyTo(localTvec);

            solvePnP(modelObjectPoints, modelImagePoints, params.camera.intrinsics, params.camera.distortion, localRvec, localTvec,
                     params.useExtrinsicGuess, params.flags);


            vector<Point2f> projected_points;
            projected_points.resize(objectPoints.cols);
            projectPoints(objectPoints, localRvec, localTvec, params.camera.intrinsics, params.camera.distortion, projected_points);

            Mat rotatedPoints;
            project3dPoints(objectPoints, localRvec, localTvec, rotatedPoints);

            vector<int> localInliers;
            for (int i = 0; i < objectPoints.cols; i++)
            {
                Point2f p(imagePoints.at<Vec2f>(0, i)[0], imagePoints.at<Vec2f>(0, i)[1]);
                if ((norm(p - projected_points[i]) < params.reprojectionError)
                    && (rotatedPoints.at<Vec3f>(0, i)[2] > 0)) //hack
                {
                    localInliers.push_back(i);
                }
            }

            if (localInliers.size() > inliers.size())
            {
                resultsMutex.lock();

                inliers.clear();
                inliers.resize(localInliers.size());
                memcpy(&inliers[0], &localInliers[0], sizeof(int) * localInliers.size());
                localRvec.copyTo(rvec);
                localTvec.copyTo(tvec);

                resultsMutex.unlock();
            }
        }

        class PnPSolver
        {
        public:
            void operator()( const BlockedRange& r ) const
            {
                vector<char> pointsMask(objectPoints.cols, 0);
                memset(&pointsMask[0], 1, MIN_POINTS_COUNT );
                for( int i=r.begin(); i!=r.end(); ++i )
                {
                    generateVar(pointsMask);
                    pnpTask(pointsMask, objectPoints, imagePoints, parameters,
                            inliers, rvec, tvec, initRvec, initTvec, syncMutex);
                    if ((int)inliers.size() >= parameters.minInliersCount)
                    {
#ifdef HAVE_TBB
                        tbb::task::self().cancel_group_execution();
#else
                        break;
#endif
                    }
                }
            }
            PnPSolver(const Mat& _objectPoints, const Mat& _imagePoints, const Parameters& _parameters,
                      Mat& _rvec, Mat& _tvec, vector<int>& _inliers):
            objectPoints(_objectPoints), imagePoints(_imagePoints), parameters(_parameters),
            rvec(_rvec), tvec(_tvec), inliers(_inliers)
            {
                rvec.copyTo(initRvec);
                tvec.copyTo(initTvec);

                generator.state = theRNG().state; //to control it somehow...
            }
        private:
            PnPSolver& operator=(const PnPSolver&);

            const Mat& objectPoints;
            const Mat& imagePoints;
            const Parameters& parameters;
            Mat &rvec, &tvec;
            vector<int>& inliers;
            Mat initRvec, initTvec;

            static RNG generator;
            static Mutex syncMutex;

            void generateVar(vector<char>& mask) const
            {
                int size = (int)mask.size();
                for (int i = 0; i < size; i++)
                {
                    int i1 = generator.uniform(0, size);
                    int i2 = generator.uniform(0, size);
                    char curr = mask[i1];
                    mask[i1] = mask[i2];
                    mask[i2] = curr;
                }
            }
        };

        Mutex PnPSolver::syncMutex;
        RNG PnPSolver::generator;

    }
}

void cv::solvePnPRansac(InputArray _opoints, InputArray _ipoints,
                        InputArray _cameraMatrix, InputArray _distCoeffs,
                        OutputArray _rvec, OutputArray _tvec, bool useExtrinsicGuess,
                        int iterationsCount, float reprojectionError, int minInliersCount,
                        OutputArray _inliers, int flags)
{
    Mat opoints = _opoints.getMat(), ipoints = _ipoints.getMat();
    Mat cameraMatrix = _cameraMatrix.getMat(), distCoeffs = _distCoeffs.getMat();

    CV_Assert(opoints.isContinuous());
    CV_Assert(opoints.depth() == CV_32F);
    CV_Assert((opoints.rows == 1 && opoints.channels() == 3) || opoints.cols*opoints.channels() == 3);
    CV_Assert(ipoints.isContinuous());
    CV_Assert(ipoints.depth() == CV_32F);
    CV_Assert((ipoints.rows == 1 && ipoints.channels() == 2) || ipoints.cols*ipoints.channels() == 2);

    _rvec.create(3, 1, CV_64FC1);
    _tvec.create(3, 1, CV_64FC1);
    Mat rvec = _rvec.getMat();
    Mat tvec = _tvec.getMat();

    Mat objectPoints = opoints.reshape(3, 1), imagePoints = ipoints.reshape(2, 1);

    if (minInliersCount <= 0)
        minInliersCount = objectPoints.cols;
    cv::pnpransac::Parameters params;
    params.iterationsCount = iterationsCount;
    params.minInliersCount = minInliersCount;
    params.reprojectionError = reprojectionError;
    params.useExtrinsicGuess = useExtrinsicGuess;
    params.camera.init(cameraMatrix, distCoeffs);
    params.flags = flags;

    vector<int> localInliers;
    Mat localRvec, localTvec;
    rvec.copyTo(localRvec);
    tvec.copyTo(localTvec);

    if (objectPoints.cols >= pnpransac::MIN_POINTS_COUNT)
    {
        parallel_for(BlockedRange(0,iterationsCount), cv::pnpransac::PnPSolver(objectPoints, imagePoints, params,
                                                                               localRvec, localTvec, localInliers));
    }

    if (localInliers.size() >= (size_t)pnpransac::MIN_POINTS_COUNT)
    {
        if (flags != CV_P3P)
        {
            int i, pointsCount = (int)localInliers.size();
            Mat inlierObjectPoints(1, pointsCount, CV_32FC3), inlierImagePoints(1, pointsCount, CV_32FC2);
            for (i = 0; i < pointsCount; i++)
            {
                int index = localInliers[i];
                Mat colInlierImagePoints = inlierImagePoints(Rect(i, 0, 1, 1));
                imagePoints.col(index).copyTo(colInlierImagePoints);
                Mat colInlierObjectPoints = inlierObjectPoints(Rect(i, 0, 1, 1));
                objectPoints.col(index).copyTo(colInlierObjectPoints);
            }
            solvePnP(inlierObjectPoints, inlierImagePoints, params.camera.intrinsics, params.camera.distortion, localRvec, localTvec, true, flags);
        }
        localRvec.copyTo(rvec);
        localTvec.copyTo(tvec);
        if (_inliers.needed())
            Mat(localInliers).copyTo(_inliers);
    }
    else
    {
        tvec.setTo(Scalar(0));
        Mat R = Mat::eye(3, 3, CV_64F);
        Rodrigues(R, rvec);
        if( _inliers.needed() )
            _inliers.release();
    }
    return;
}
