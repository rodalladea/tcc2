/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class HardwareDetector */

#ifndef _Included_HardwareDetector
#define _Included_HardwareDetector

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     org_opencv_engine_HardwareDetector
 * Method:    GetCpuID
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_opencv_engine_HardwareDetector_GetCpuID
(JNIEnv *, jclass);

/*
 * Class:     org_opencv_engine_HardwareDetector
 * Method:    GetPlatformName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_opencv_engine_HardwareDetector_GetPlatformName
(JNIEnv *, jclass);

/*
 * Class:     org_opencv_engine_HardwareDetector
 * Method:    GetProcessorCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_opencv_engine_HardwareDetector_GetProcessorCount
(JNIEnv *, jclass);

/*
 * Class:     org_opencv_engine_HardwareDetector
 * Method:    DetectKnownPlatforms
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_opencv_engine_HardwareDetector_DetectKnownPlatforms
(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif

#endif
