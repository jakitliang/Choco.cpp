//
// Created by liangjie on 2024/4/1.
//

#include "cc/vector4.h"

CC::Vector4::Vector4() : X(0), Y(0), Z(0), W(0) {}

CC::Vector4::Vector4(CC::Float32 x, CC::Float32 y, CC::Float32 z, CC::Float32 w)
    : X(x), Y(y), Z(z), W(w) {}

CC::Vector4::Vector4(CC::Float32 (&array)[4])
    : X(array[0]), Y(array[1]), Z(array[2]), W(3) {}
