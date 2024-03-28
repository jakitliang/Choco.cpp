//
// Created by liangjie on 2024/3/26.
//

#ifndef CHOCO_CPP_PIXELS_H
#define CHOCO_CPP_PIXELS_H

#include "cc/types.h"

namespace CC::Pixel {
    struct Type {
        static const UInt32 Unknown;
        static const UInt32 Index1;
        static const UInt32 Index4;
        static const UInt32 Index8;
        static const UInt32 Packed8;
        static const UInt32 Packed16;
        static const UInt32 Packed32;
        static const UInt32 ArrayU8;
        static const UInt32 ArrayU16;
        static const UInt32 ArrayU32;
        static const UInt32 ArrayF16;
        static const UInt32 ArrayF32;
    };

    struct BitmapOrder {
        static const UInt32 None;
        static const UInt32 By4321;
        static const UInt32 By1234;
    };

    struct Format {
        static const UInt32 UNKNOWN;
        static const UInt32 INDEX1LSB;
        static const UInt32 INDEX1MSB;
        static const UInt32 INDEX4LSB;
        static const UInt32 INDEX4MSB;
        static const UInt32 INDEX8;
        static const UInt32 RGB332;
        static const UInt32 XRGB4444;
        static const UInt32 RGB444;
        static const UInt32 XBGR4444;
        static const UInt32 BGR444;
        static const UInt32 XRGB1555;
        static const UInt32 RGB555;
        static const UInt32 XBGR1555;
        static const UInt32 BGR555;
        static const UInt32 ARGB4444;
        static const UInt32 RGBA4444;
        static const UInt32 ABGR4444;
        static const UInt32 BGRA4444;
        static const UInt32 ARGB1555;
        static const UInt32 RGBA5551;
        static const UInt32 ABGR1555;
        static const UInt32 BGRA5551;
        static const UInt32 RGB565;
        static const UInt32 BGR565;
        static const UInt32 RGB24;
        static const UInt32 BGR24;
        static const UInt32 XRGB8888;
        static const UInt32 RGB888;
        static const UInt32 RGBX8888;
        static const UInt32 XBGR8888;
        static const UInt32 BGR888;
        static const UInt32 BGRX8888;
        static const UInt32 ARGB8888;
        static const UInt32 RGBA8888;
        static const UInt32 ABGR8888;
        static const UInt32 BGRA8888;
        static const UInt32 ARGB2101010;

        // 32bit
        static const UInt32 RGBA32;
        static const UInt32 ARGB32;
        static const UInt32 BGRA32;
        static const UInt32 ABGR32;

        // video
        static const UInt32 YV12;
        static const UInt32 IYUV;
        static const UInt32 YUY2;
        static const UInt32 UYVY;
        static const UInt32 YVYU;
        static const UInt32 NV12;
        static const UInt32 NV21;
        static const UInt32 EXTERNAL_OES;
    };
}

#endif //CHOCO_CPP_PIXELS_H
