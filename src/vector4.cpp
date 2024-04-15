//
// Created by liangjie on 2024/4/1.
//

#include "cc/vector4.h"
#include <cmath>

const CC::Float32 Epsilon = 0.01f;

CC::Vector4 &CC::Vector4::operator+(const CC::Vector4 &another) {
    X += another.X;
    Y += another.Y;
    Z += another.Z;
    W += another.W;

    return *this;
}

CC::Vector4 &CC::Vector4::operator-(const CC::Vector4 &another) {
    X -= another.X;
    Y -= another.Y;
    Z -= another.Z;
    W -= another.W;

    return *this;
}

CC::Vector4 &CC::Vector4::operator*(CC::Float32 num) {
    X *= num;
    Y *= num;
    Z *= num;
    W *= num;

    return *this;
}

CC::Vector4 &CC::Vector4::operator/(CC::Float32 num) {
    X /= num;
    Y /= num;
    Z /= num;
    W /= num;

    return *this;
}

bool CC::Vector4::operator!=(const CC::Vector4 &another) const {
    if (fabs(X - another.X) < Epsilon) return false;

    if (fabs(Y - another.Y) < Epsilon) return false;

    if (fabs(Z - another.Z) < Epsilon) return false;

    if (fabs(W - another.W) < Epsilon) return false;

    return true;
}

bool CC::Vector4::operator==(const CC::Vector4 &another) const {
    return !operator!=(another);
}

CC::Vector4 CC::Vector4::Zero() {
    return {0, 0, 0, 0};
}
