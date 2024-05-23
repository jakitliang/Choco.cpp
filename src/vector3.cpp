//
// Created by liangjie on 2024/4/15.
//

#include "cc/vector3.h"
#include <cmath>

const CC::Float32 Epsilon = 0.01f;

void CC::Vector3::Cross(const CC::Vector3 &rhs) {
    *this = Cross(*this, rhs);
}

void CC::Vector3::Normalize() {
    *this = Normalize(*this);
}

CC::Vector3 CC::Vector3::operator+(CC::Float32 rhs) const {
    return {X + rhs, Y + rhs, Z + rhs};
}

CC::Vector3 CC::Vector3::operator+(const CC::Vector3 &rhs) const {
    return {X + rhs.X, Y + rhs.Y, Z + rhs.Z};
}

CC::Vector3 CC::Vector3::operator-(CC::Float32 rhs) const {
    return {X - rhs, Y - rhs, Z - rhs};
}

CC::Vector3 CC::Vector3::operator-(const CC::Vector3 &rhs) const {
    return {X - rhs.X, Y - rhs.Y, Z - rhs.Z};
}

CC::Vector3 CC::Vector3::operator*(Float32 rhs) const {
    return {X * rhs, Y * rhs, Z * rhs};
}

CC::Vector3 CC::Vector3::operator*(const CC::Vector3 &rhs) const {
    return {X * rhs.X, Y * rhs.Y, Z * rhs.Z};
}

CC::Vector3 CC::Vector3::operator/(Float32 rhs) const {
    return {X / rhs, Y / rhs, Z / rhs};
}

CC::Vector3 CC::Vector3::operator/(const CC::Vector3 &rhs) const {
    return {X / rhs.X, Y / rhs.Y, Z / rhs.Z};
}

CC::Vector3 &CC::Vector3::operator+=(CC::Float32 rhs) {
    X += rhs;
    Y += rhs;
    Z += rhs;

    return *this;
}

CC::Vector3 &CC::Vector3::operator+=(const CC::Vector3 &rhs) {
    X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;

    return *this;
}

CC::Vector3 &CC::Vector3::operator-=(CC::Float32 rhs) {
    X -= rhs;
    Y -= rhs;
    Z -= rhs;

    return *this;
}

CC::Vector3 &CC::Vector3::operator-=(const CC::Vector3 &rhs) {
    X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;

    return *this;
}

CC::Vector3 &CC::Vector3::operator*=(Float32 rhs) {
    X *= rhs;
    Y *= rhs;
    Z *= rhs;

    return *this;
}

CC::Vector3 &CC::Vector3::operator*=(const CC::Vector3 &rhs) {
    X *= rhs.X;
    Y *= rhs.Y;
    Z *= rhs.Z;

    return *this;
}

CC::Vector3 &CC::Vector3::operator/=(Float32 rhs) {
    X /= rhs;
    Y /= rhs;
    Z /= rhs;

    return *this;
}

CC::Vector3 &CC::Vector3::operator/=(const CC::Vector3 &rhs) {
    X /= rhs.X;
    Y /= rhs.Y;
    Z /= rhs.Z;

    return *this;
}

bool CC::Vector3::operator!=(const CC::Vector3 &rhs) const {
    if (fabs(X - rhs.X) < Epsilon) return false;

    if (fabs(Y - rhs.Y) < Epsilon) return false;

    if (fabs(Z - rhs.Z) < Epsilon) return false;

    return true;
}

bool CC::Vector3::operator==(const CC::Vector3 &rhs) const {
    return !operator!=(rhs);
}

CC::Float32 &CC::Vector3::operator[](CC::Size index) {
    return Row[index];
}

const CC::Float32 &CC::Vector3::operator[](CC::Size index) const {
    return Row[index];
}

CC::Vector3 CC::Vector3::Zero() {
    return {0, 0, 0};
}

CC::Vector3 CC::Vector3::Cross(const CC::Vector3 &a, const CC::Vector3 &b) {
    return {a.Y * b.Z - a.Z * b.Y,
            a.Z * b.X - a.X * b.Z,
            a.X * b.Y - a.Y * b.X};
}

CC::Vector3 CC::Vector3::Normalize(const CC::Vector3 &v) {
    auto ret = v * v;
    auto scalar = ret.X + ret.Y + ret.Z;
    auto inv = 1 / sqrt(scalar);
    return v * inv;
}
