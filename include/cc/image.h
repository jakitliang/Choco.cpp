//
// Created by liangjie on 2024/4/1.
//

#ifndef CHOCO_CPP_IMAGE_H
#define CHOCO_CPP_IMAGE_H

#include "cc/handle.h"
#include "cc/types.h"

namespace CC {
    struct Image {
        ~Image();

        bool Open(Handle * rendererHandle, const char * fileName);

        bool Open(Handle * rendererHandle, const void * buffer, Size size);

        bool Open(Handle * rendererHandle, Handle * imageData);

        void Close();
    };
}

#endif //CHOCO_CPP_IMAGE_H
