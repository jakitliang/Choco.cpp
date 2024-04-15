//
// Created by liangjie on 2024/4/1.
//

#include "cc/vector2.h"
#include <cmath>

const CC::Float32 Epsilon = 0.01f;

CC::Vector2 &CC::Vector2::operator+(const CC::Vector2 &another) {
    X += another.X;
    Y += another.Y;

    return *this;
}

CC::Vector2 &CC::Vector2::operator-(const CC::Vector2 &another) {
    X -= another.X;
    Y -= another.Y;

    return *this;
}

CC::Vector2 &CC::Vector2::operator*(CC::Float32 num) {
    X *= num;
    Y *= num;

    return *this;
}

CC::Vector2 &CC::Vector2::operator/(CC::Float32 num) {
    X /= num;
    Y /= num;

    return *this;
}

bool CC::Vector2::operator!=(const CC::Vector2 &another) const {
    if (fabs(X - another.X) < Epsilon) return false;

    if (fabs(Y - another.Y) < Epsilon) return false;

    return true;
}

bool CC::Vector2::operator==(const CC::Vector2 &another) const {
    return !operator!=(another);
}

CC::Vector2 CC::Vector2::Zero() {
    return {0, 0};
}
