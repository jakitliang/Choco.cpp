//
// Created by Jakit Liang on 2024/4/1.
//

#include "cc/vector2.h"
#include <cmath>

const CC::Float32 Epsilon = 0.01f;

CC::Vector2 CC::Vector2::operator+(Float32 rhs) const {
    return {X + rhs, Y + rhs};
}

CC::Vector2 CC::Vector2::operator+(const CC::Vector2 &rhs) const {
    return {X + rhs.X, Y + rhs.Y};
}

CC::Vector2 CC::Vector2::operator-(Float32 rhs) const {
    return {X - rhs, Y - rhs};
}

CC::Vector2 CC::Vector2::operator-(const CC::Vector2 &rhs) const {
    return {X - rhs.X, Y - rhs.Y};
}

CC::Vector2 CC::Vector2::operator*(CC::Float32 num) const {
    return {X * num, Y * num};
}

CC::Vector2 CC::Vector2::operator*(const CC::Vector2 &rhs) const {
    return {X * rhs.X, Y * rhs.Y};
}

CC::Vector2 CC::Vector2::operator/(CC::Float32 num) const {
    return {X / num, Y / num};
}

CC::Vector2 CC::Vector2::operator/(const CC::Vector2 &rhs) const {
    return {X / rhs.X, Y / rhs.Y};
}

CC::Vector2 &CC::Vector2::operator+=(Float32 rhs) {
    X += rhs;
    Y += rhs;

    return *this;
}

CC::Vector2 &CC::Vector2::operator+=(const CC::Vector2 &rhs) {
    X += rhs.X;
    Y += rhs.Y;

    return *this;
}

CC::Vector2 &CC::Vector2::operator-=(Float32 rhs) {
    X -= rhs;
    Y -= rhs;

    return *this;
}

CC::Vector2 &CC::Vector2::operator-=(const CC::Vector2 &rhs) {
    X -= rhs.X;
    Y -= rhs.Y;

    return *this;
}

CC::Vector2 &CC::Vector2::operator*=(CC::Float32 num) {
    X *= num;
    Y *= num;

    return *this;
}

CC::Vector2 &CC::Vector2::operator*=(const CC::Vector2 &rhs) {
    X *= rhs.X;
    Y *= rhs.Y;

    return *this;
}

CC::Vector2 &CC::Vector2::operator/=(CC::Float32 num) {
    X /= num;
    Y /= num;

    return *this;
}

CC::Vector2 &CC::Vector2::operator/=(const CC::Vector2 &rhs) {
    X /= rhs.X;
    Y /= rhs.Y;

    return *this;
}

bool CC::Vector2::operator!=(const CC::Vector2 &rhs) const {
    if (fabs(X - rhs.X) < Epsilon) return false;

    if (fabs(Y - rhs.Y) < Epsilon) return false;

    return true;
}

bool CC::Vector2::operator==(const CC::Vector2 &rhs) const {
    return !operator!=(rhs);
}

CC::Float32 &CC::Vector2::operator[](CC::Size index) {
    return Row[index];
}

const CC::Float32 &CC::Vector2::operator[](CC::Size index) const {
    return Row[index];
}

CC::Vector2 CC::Vector2::Zero() {
    return {0, 0};
}
