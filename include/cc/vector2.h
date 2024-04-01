//
// Created by liangjie on 2024/4/1.
//

#ifndef CHOCO_CPP_VECTOR2_H
#define CHOCO_CPP_VECTOR2_H

#include "cc/types.h"

namespace CC {
    struct Vector2 {
        Float32 X;
        Float32 Y;

        Vector2();

        Vector2(const Vector2 & vector2) = default;

        Vector2(Float32 x, Float32 y);

        Vector2(Float32 (&array)[2]);
    };
}

#endif //CHOCO_CPP_VECTOR2_H
