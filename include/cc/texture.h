//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_TEXTURE_H
#define CHOCO_CPP_TEXTURE_H

#include "cc/flags.h"
#include "cc/vector2.h"

namespace CC {
    struct Texture {
        virtual ~Texture() = default;

        Float32 GetWidth();

        Float32 GetHeight();

        Vector2 GetSize();

        virtual void * GetHandle() = 0;
    };
}

#endif //CHOCO_CPP_TEXTURE_H
