//
// Created by liangjie on 2024/4/1.
//

#ifndef CHOCO_CPP_VECTOR4_H
#define CHOCO_CPP_VECTOR4_H

#include "cc/types.h"

namespace CC {
    struct Vector4 {
        Float32 X;
        Float32 Y;
        Float32 Z;
        Float32 W;

        Vector4();

        Vector4(const Vector4 & vector4) = default;

        Vector4(Float32 x, Float32 y, Float32 z, Float32 w);

        Vector4(Float32 (&array)[4]);
    };
}

#endif //CHOCO_CPP_VECTOR4_H
