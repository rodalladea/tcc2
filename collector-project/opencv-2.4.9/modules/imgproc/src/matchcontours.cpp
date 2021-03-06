/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
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
//   * The name of Intel Corporation may not be used to endorse or promote products
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

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvMatchContours
//    Purpose:
//      Calculates matching of the two contours
//    Context:
//    Parameters:
//      contour_1 - pointer to the first input contour object.
//      contour_2 - pointer to the second input contour object.
//      method - method for the matching calculation
//      (now CV_IPPI_CONTOURS_MATCH_I1, CV_CONTOURS_MATCH_I2 or
//      CV_CONTOURS_MATCH_I3 only  )
//      rezult - output calculated measure
//
//F*/
CV_IMPL  double
cvMatchShapes( const void* contour1, const void* contour2,
               int method, double /*parameter*/ )
{
    CvMoments moments;
    CvHuMoments huMoments;
    double ma[7], mb[7];
    int i, sma, smb;
    double eps = 1.e-5;
    double mmm;
    double result = 0;

    if( !contour1 || !contour2 )
        CV_Error( CV_StsNullPtr, "" );

    // calculate moments of the first shape
    cvMoments( contour1, &moments );
    cvGetHuMoments( &moments, &huMoments );

    ma[0] = huMoments.hu1;
    ma[1] = huMoments.hu2;
    ma[2] = huMoments.hu3;
    ma[3] = huMoments.hu4;
    ma[4] = huMoments.hu5;
    ma[5] = huMoments.hu6;
    ma[6] = huMoments.hu7;


    // calculate moments of the second shape
    cvMoments( contour2, &moments );
    cvGetHuMoments( &moments, &huMoments );

    mb[0] = huMoments.hu1;
    mb[1] = huMoments.hu2;
    mb[2] = huMoments.hu3;
    mb[3] = huMoments.hu4;
    mb[4] = huMoments.hu5;
    mb[5] = huMoments.hu6;
    mb[6] = huMoments.hu7;

    switch (method)
    {
    case 1:
        {
            for( i = 0; i < 7; i++ )
            {
                double ama = fabs( ma[i] );
                double amb = fabs( mb[i] );

                if( ma[i] > 0 )
                    sma = 1;
                else if( ma[i] < 0 )
                    sma = -1;
                else
                    sma = 0;
                if( mb[i] > 0 )
                    smb = 1;
                else if( mb[i] < 0 )
                    smb = -1;
                else
                    smb = 0;

                if( ama > eps && amb > eps )
                {
                    ama = 1. / (sma * log10( ama ));
                    amb = 1. / (smb * log10( amb ));
                    result += fabs( -ama + amb );
                }
            }
            break;
        }

    case 2:
        {
            for( i = 0; i < 7; i++ )
            {
                double ama = fabs( ma[i] );
                double amb = fabs( mb[i] );

                if( ma[i] > 0 )
                    sma = 1;
                else if( ma[i] < 0 )
                    sma = -1;
                else
                    sma = 0;
                if( mb[i] > 0 )
                    smb = 1;
                else if( mb[i] < 0 )
                    smb = -1;
                else
                    smb = 0;

                if( ama > eps && amb > eps )
                {
                    ama = sma * log10( ama );
                    amb = smb * log10( amb );
                    result += fabs( -ama + amb );
                }
            }
            break;
        }

    case 3:
        {
            for( i = 0; i < 7; i++ )
            {
                double ama = fabs( ma[i] );
                double amb = fabs( mb[i] );

                if( ma[i] > 0 )
                    sma = 1;
                else if( ma[i] < 0 )
                    sma = -1;
                else
                    sma = 0;
                if( mb[i] > 0 )
                    smb = 1;
                else if( mb[i] < 0 )
                    smb = -1;
                else
                    smb = 0;

                if( ama > eps && amb > eps )
                {
                    ama = sma * log10( ama );
                    amb = smb * log10( amb );
                    mmm = fabs( (ama - amb) / ama );
                    if( result < mmm )
                        result = mmm;
                }
            }
            break;
        }
    default:
        CV_Error( CV_StsBadArg, "Unknown comparison method" );
    }

    return result;
}


/* End of file. */
