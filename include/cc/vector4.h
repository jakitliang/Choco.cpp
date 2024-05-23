//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/4/1.
//

#ifndef CHOCO_CPP_VECTOR4_H
#define CHOCO_CPP_VECTOR4_H

#include "cc/types.h"

namespace CC {
    struct Vector4 {
        union {
            struct {
                union {
                    Float32 X, R, S;
                };

                union {
                    Float32 Y, G, T;
                };

                union {
                    Float32 Z, B, P, Width;
                };

                union {
                    Float32 W, A, Q, Height;
                };
            };

            Float32 Row[4];
        };

        Vector4 operator+(Float32 rhs) const;

        Vector4 operator+(const Vector4 & rhs) const;

        Vector4 operator-(Float32 rhs) const;

        Vector4 operator-(const Vector4 & rhs) const;

        Vector4 operator*(Float32 rhs) const;

        Vector4 operator*(const Vector4 & rhs) const;

        Vector4 operator/(Float32 rhs) const;

        Vector4 & operator+=(Float32 rhs);

        Vector4 & operator+=(const Vector4 & rhs);

        Vector4 & operator-=(Float32 rhs);

        Vector4 & operator-=(const Vector4 & rhs);

        Vector4 & operator*=(Float32 rhs);

        Vector4 & operator*=(const Vector4 & rhs);

        Vector4 & operator/=(Float32 rhs);

        bool operator==(const Vector4 & rhs) const;

        bool operator!=(const Vector4 & rhs) const;

        Float32 &operator[](Size index);

        const Float32 &operator[](Size index) const;

        static Vector4 Zero();
    };
}

#endif //CHOCO_CPP_VECTOR4_H
