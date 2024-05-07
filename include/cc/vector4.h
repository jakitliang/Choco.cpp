//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/4/1.
//

#ifndef CHOCO_CPP_VECTOR4_H
#define CHOCO_CPP_VECTOR4_H

#include "cc/types.h"

namespace CC {
    struct Vector4 {
        union {Float32 X; Float32 R;};
        union {Float32 Y; Float32 G;};
        union {Float32 Z; Float32 B; Float32 Width;};
        union {Float32 W; Float32 A; Float32 Height;};

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
