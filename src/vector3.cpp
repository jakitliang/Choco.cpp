//
// Created by liangjie on 2024/4/15.
//

#include "cc/vector3.h"
#include <cmath>

const CC::Float32 Epsilon = 0.01f;

CC::Vector3 &CC::Vector3::operator+(const CC::Vector3 &another) {
    X += another.X;
    Y += another.Y;
    Z += another.Z;

    return *this;
}

CC::Vector3 &CC::Vector3::operator-(const CC::Vector3 &another) {
    X -= another.X;
    Y -= another.Y;
    Z -= another.Z;

    return *this;
}

CC::Vector3 &CC::Vector3::operator*(Float32 num) {
    X *= num;
    Y *= num;
    Z *= num;

    return *this;
}

CC::Vector3 &CC::Vector3::operator/(Float32 num) {
    X /= num;
    Y /= num;
    Z /= num;

    return *this;
}

bool CC::Vector3::operator!=(const CC::Vector3 &another) const {
    if (fabs(X - another.X) < Epsilon) return false;

    if (fabs(Y - another.Y) < Epsilon) return false;

    if (fabs(Z - another.Z) < Epsilon) return false;

    return true;
}

bool CC::Vector3::operator==(const CC::Vector3 &another) const {
    return !operator!=(another);
}

CC::Vector3 CC::Vector3::Zero() {
    return {0, 0, 0};
}
