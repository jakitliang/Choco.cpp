//
// Created by liangjie on 2024/4/1.
//

#include "cc/vector4.h"
#include <cmath>

const CC::Float32 Epsilon = 0.01f;

CC::Vector4 CC::Vector4::operator+(CC::Float32 rhs) const {
    return {X + rhs, Y + rhs, Z + rhs, W + rhs};
}

CC::Vector4 CC::Vector4::operator+(const CC::Vector4 &rhs) const {
    return {X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W};
}

CC::Vector4 CC::Vector4::operator-(CC::Float32 rhs) const {
    return {X - rhs, Y - rhs, Z - rhs, W - rhs};
}

CC::Vector4 CC::Vector4::operator-(const CC::Vector4 &rhs) const {
    return {X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W};
}

CC::Vector4 CC::Vector4::operator*(CC::Float32 rhs) const {
    return {X * rhs, Y * rhs, Z * rhs, W * rhs};
}

CC::Vector4 CC::Vector4::operator*(const CC::Vector4 &rhs) const {
    return {X * rhs.X, Y * rhs.Y, Z * rhs.Z, W * rhs.W};
}

CC::Vector4 CC::Vector4::operator/(CC::Float32 rhs) const {
    return {X / rhs, Y / rhs, Z / rhs, W / rhs};
}

CC::Vector4 &CC::Vector4::operator+=(CC::Float32 rhs) {
    X += rhs;
    Y += rhs;
    Z += rhs;
    W += rhs;

    return *this;
}

CC::Vector4 &CC::Vector4::operator+=(const CC::Vector4 &rhs) {
    X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;
    W += rhs.W;

    return *this;
}

CC::Vector4 &CC::Vector4::operator-=(CC::Float32 rhs) {
    X -= rhs;
    Y -= rhs;
    Z -= rhs;
    W -= rhs;

    return *this;
}

CC::Vector4 &CC::Vector4::operator-=(const CC::Vector4 &rhs) {
    X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;
    W -= rhs.W;

    return *this;
}

CC::Vector4 &CC::Vector4::operator*=(CC::Float32 rhs) {
    X *= rhs;
    Y *= rhs;
    Z *= rhs;
    W *= rhs;

    return *this;
}

CC::Vector4 &CC::Vector4::operator*=(const CC::Vector4 &rhs) {
    X *= rhs.X;
    Y *= rhs.Y;
    Z *= rhs.Z;
    W *= rhs.W;

    return *this;
}

CC::Vector4 &CC::Vector4::operator/=(CC::Float32 rhs) {
    X /= rhs;
    Y /= rhs;
    Z /= rhs;
    W /= rhs;

    return *this;
}

bool CC::Vector4::operator!=(const CC::Vector4 &rhs) const {
    if (fabs(X - rhs.X) < Epsilon) return false;

    if (fabs(Y - rhs.Y) < Epsilon) return false;

    if (fabs(Z - rhs.Z) < Epsilon) return false;

    if (fabs(W - rhs.W) < Epsilon) return false;

    return true;
}

bool CC::Vector4::operator==(const CC::Vector4 &rhs) const {
    return !operator!=(rhs);
}

CC::Float32 &CC::Vector4::operator[](CC::Size index) {
    return Row[index];
}

const CC::Float32 &CC::Vector4::operator[](CC::Size index) const {
    return Row[index];
}

CC::Vector4 CC::Vector4::Zero() {
    return {0, 0, 0, 0};
}
