//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/4/15.
//

#ifndef CHOCO_CPP_VECTOR3_H
#define CHOCO_CPP_VECTOR3_H

#include "cc/types.h"

namespace CC {
    struct Vector3 {
        Float32 X;
        Float32 Y;
        Float32 Z;

        Vector3 & operator+(const Vector3 & another);

        Vector3 & operator-(const Vector3 & another);

        Vector3 & operator*(Float32 num);

        Vector3 & operator/(Float32 num);

        bool operator==(const Vector3 & another) const;

        bool operator!=(const Vector3 & another) const;

        static Vector3 Zero();
    };
}

#endif //CHOCO_CPP_VECTOR3_H
