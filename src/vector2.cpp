//
// Created by liangjie on 2024/4/1.
//

#include "cc/vector2.h"

CC::Vector2::Vector2() : X(0), Y(0) {}

CC::Vector2::Vector2(Float32 x, Float32 y) : X(x), Y(y) {}

CC::Vector2::Vector2(Float32 (&array)[2]) : X(array[0]), Y(array[1]) {}
