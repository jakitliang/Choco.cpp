//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/4/1.
//

#ifndef CHOCO_CPP_VECTOR2_H
#define CHOCO_CPP_VECTOR2_H

#include "cc/types.h"

namespace CC {
    struct Vector2 {
        Float32 X;
        Float32 Y;

        Vector2 & operator+(const Vector2 & another);

        Vector2 & operator-(const Vector2 & another);

        Vector2 & operator*(Float32 num);

        Vector2 & operator/(Float32 num);

        bool operator==(const Vector2 & another) const;

        bool operator!=(const Vector2 & another) const;

        static Vector2 Zero();
    };
}

#endif //CHOCO_CPP_VECTOR2_H
