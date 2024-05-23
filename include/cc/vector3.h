//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/4/15.
//

#ifndef CHOCO_CPP_VECTOR3_H
#define CHOCO_CPP_VECTOR3_H

#include "cc/types.h"

namespace CC {
    struct Vector3 {
        union {
            struct {
                union {
                    Float32 X, R, S;
                };

                union {
                    Float32 Y, G, T;
                };

                union {
                    Float32 Z, B, P;
                };
            };

            Float32 Row[3];
        };

        void Cross(const Vector3 &rhs);

        void Normalize();

        Vector3 operator+(Float32 rhs) const;

        Vector3 operator+(const Vector3 & rhs) const;

        Vector3 operator-(Float32 rhs) const;

        Vector3 operator-(const Vector3 & rhs) const;

        Vector3 operator*(Float32 rhs) const;

        Vector3 operator*(const Vector3 & rhs) const;

        Vector3 operator/(Float32 rhs) const;

        Vector3 operator/(const Vector3 & rhs) const;

        Vector3 & operator+=(Float32 rhs);

        Vector3 & operator+=(const Vector3 & rhs);

        Vector3 & operator-=(Float32 rhs);

        Vector3 & operator-=(const Vector3 & rhs);

        Vector3 & operator*=(Float32 rhs);

        Vector3 & operator*=(const Vector3 & rhs);

        Vector3 & operator/=(Float32 rhs);

        Vector3 & operator/=(const Vector3 & rhs);

        bool operator==(const Vector3 & rhs) const;

        bool operator!=(const Vector3 & rhs) const;

        Float32 &operator[](Size index);

        const Float32 &operator[](Size index) const;

        static Vector3 Zero();

        static Vector3 Cross(const Vector3 &a, const Vector3 &b);

        static Vector3 Normalize(const Vector3 &v);
    };
}

#endif //CHOCO_CPP_VECTOR3_H
