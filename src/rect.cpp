//
// Created by liangjie on 2024/4/1.
//

#include "cc/rect.h"

CC::Rect::Rect() : X(0), Y(0), Width(0), Height(0) {}

CC::Rect::Rect(CC::Float32 x, CC::Float32 y, CC::Float32 width, CC::Float32 height)
    : X(x), Y(y), Width(width), Height(height) {}

CC::Rect::Rect(CC::Float32 (&array)[4])
    : X(array[0]), Y(array[1]), Width(array[2]), Height(array[3]) {}

