//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/4/1.
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

        Vector4 & operator+(const Vector4 & another);

        Vector4 & operator-(const Vector4 & another);

        Vector4 & operator*(Float32 num);

        Vector4 & operator/(Float32 num);

        bool operator==(const Vector4 & another) const;

        bool operator!=(const Vector4 & another) const;

        static Vector4 Zero();
    };
}

#endif //CHOCO_CPP_VECTOR4_H
