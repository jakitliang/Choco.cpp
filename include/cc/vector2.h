//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/4/1.
//

#ifndef CHOCO_CPP_VECTOR2_H
#define CHOCO_CPP_VECTOR2_H

#include "cc/types.h"

namespace CC {
    struct Vector2 {
        union {
            struct {
                union {
                    Float32 X, R, S, Width;
                };

                union {
                    Float32 Y, G, T, Height;
                };
            };

            Float32 Row[2];
        };

        Vector2 operator+(Float32 rhs) const;

        Vector2 operator+(const Vector2 & rhs) const;

        Vector2 operator-(Float32 rhs) const;

        Vector2 operator-(const Vector2 & rhs) const;

        Vector2 operator*(Float32 num) const;

        Vector2 operator*(const Vector2 & rhs) const;

        Vector2 operator/(Float32 num) const;

        Vector2 operator/(const Vector2 & rhs) const;

        Vector2 & operator+=(Float32 rhs);

        Vector2 & operator+=(const Vector2 & rhs);

        Vector2 & operator-=(Float32 rhs);

        Vector2 & operator-=(const Vector2 & rhs);

        Vector2 & operator*=(Float32 num);

        Vector2 & operator*=(const Vector2 & rhs);

        Vector2 & operator/=(Float32 num);

        Vector2 & operator/=(const Vector2 & rhs);

        bool operator==(const Vector2 & rhs) const;

        bool operator!=(const Vector2 & rhs) const;

        Float32 & operator[](Size index);

        const Float32 & operator[](Size index) const;

        static Vector2 Zero();
    };
}

#endif //CHOCO_CPP_VECTOR2_H
