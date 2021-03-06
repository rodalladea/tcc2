#ifndef CAMERA_PROPERTIES_H
#define CAMERA_PROPERTIES_H

enum {
    ANDROID_CAMERA_PROPERTY_FRAMEWIDTH = 0,
    ANDROID_CAMERA_PROPERTY_FRAMEHEIGHT = 1,
    ANDROID_CAMERA_PROPERTY_SUPPORTED_PREVIEW_SIZES_STRING = 2,
    ANDROID_CAMERA_PROPERTY_PREVIEW_FORMAT_STRING = 3,
    ANDROID_CAMERA_PROPERTY_FPS = 4,
    ANDROID_CAMERA_PROPERTY_EXPOSURE = 5,
    ANDROID_CAMERA_PROPERTY_FLASH_MODE = 101,
    ANDROID_CAMERA_PROPERTY_FOCUS_MODE = 102,
    ANDROID_CAMERA_PROPERTY_WHITE_BALANCE = 103,
    ANDROID_CAMERA_PROPERTY_ANTIBANDING = 104,
    ANDROID_CAMERA_PROPERTY_FOCAL_LENGTH = 105,
    ANDROID_CAMERA_PROPERTY_FOCUS_DISTANCE_NEAR = 106,
    ANDROID_CAMERA_PROPERTY_FOCUS_DISTANCE_OPTIMAL = 107,
    ANDROID_CAMERA_PROPERTY_FOCUS_DISTANCE_FAR = 108,
    ANDROID_CAMERA_PROPERTY_EXPOSE_LOCK = 109,
    ANDROID_CAMERA_PROPERTY_WHITEBALANCE_LOCK = 110
};


enum {
    ANDROID_CAMERA_FLASH_MODE_AUTO = 0,
    ANDROID_CAMERA_FLASH_MODE_OFF,
    ANDROID_CAMERA_FLASH_MODE_ON,
    ANDROID_CAMERA_FLASH_MODE_RED_EYE,
    ANDROID_CAMERA_FLASH_MODE_TORCH,
    ANDROID_CAMERA_FLASH_MODES_NUM
};

enum {
    ANDROID_CAMERA_FOCUS_MODE_AUTO = 0,
    ANDROID_CAMERA_FOCUS_MODE_CONTINUOUS_VIDEO,
    ANDROID_CAMERA_FOCUS_MODE_EDOF,
    ANDROID_CAMERA_FOCUS_MODE_FIXED,
    ANDROID_CAMERA_FOCUS_MODE_INFINITY,
    ANDROID_CAMERA_FOCUS_MODE_MACRO,
    ANDROID_CAMERA_FOCUS_MODE_CONTINUOUS_PICTURE,
    ANDROID_CAMERA_FOCUS_MODES_NUM
};

enum {
    ANDROID_CAMERA_WHITE_BALANCE_AUTO = 0,
    ANDROID_CAMERA_WHITE_BALANCE_CLOUDY_DAYLIGHT,
    ANDROID_CAMERA_WHITE_BALANCE_DAYLIGHT,
    ANDROID_CAMERA_WHITE_BALANCE_FLUORESCENT,
    ANDROID_CAMERA_WHITE_BALANCE_INCANDESCENT,
    ANDROID_CAMERA_WHITE_BALANCE_SHADE,
    ANDROID_CAMERA_WHITE_BALANCE_TWILIGHT,
    ANDROID_CAMERA_WHITE_BALANCE_WARM_FLUORESCENT,
    ANDROID_CAMERA_WHITE_BALANCE_MODES_NUM
};

enum {
    ANDROID_CAMERA_ANTIBANDING_50HZ = 0,
    ANDROID_CAMERA_ANTIBANDING_60HZ,
    ANDROID_CAMERA_ANTIBANDING_AUTO,
    ANDROID_CAMERA_ANTIBANDING_OFF,
    ANDROID_CAMERA_ANTIBANDING_MODES_NUM
};

enum {
    ANDROID_CAMERA_FOCUS_DISTANCE_NEAR_INDEX = 0,
    ANDROID_CAMERA_FOCUS_DISTANCE_OPTIMAL_INDEX,
    ANDROID_CAMERA_FOCUS_DISTANCE_FAR_INDEX
};

#endif // CAMERA_PROPERTIES_H
