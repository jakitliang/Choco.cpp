//
// Created by liangjie on 2024/4/1.
//

#ifndef CHOCO_CPP_IMAGE_DATA_H
#define CHOCO_CPP_IMAGE_DATA_H

#include "cc/handle.h"

namespace CC {
    struct ImageData : Handle {
        ~ImageData() noexcept override;

        bool Open(UInt32 flags, Int32 width, Int32 height, Int32 depth,
                  UInt32 RMask, UInt32 GMask, UInt32 BMask, UInt32 AMask);

        bool Open(UInt32 flags, Int32 width, Int32 height, Int32 depth, UInt32 format);

        bool Open(void * pixels,
                  Int32 width, Int32 height,
                  Int32 depth, Int32 pitch,
                  UInt32 RMask, UInt32 GMask, UInt32 BMask, UInt32 AMask);

        bool Open(void * pixels, Int32 width, Int32 height, Int32 depth, Int32 pitch, UInt32 format);

        bool Open(const char * fileName);

        bool Open(const void * buffer, Size size);

        void Close();
    };
}

#endif //CHOCO_CPP_IMAGE_DATA_H
