//
// Created by liangjie on 2024/4/1.
//

#ifndef CHOCO_CPP_RECT_H
#define CHOCO_CPP_RECT_H

#include "cc/vector2.h"

namespace CC {
    struct Rect {
        Float32 X;
        Float32 Y;
        Float32 Width;
        Float32 Height;

        Rect();

        Rect(const Rect & rect) = default;

        Rect(Float32 x, Float32 y, Float32 width, Float32 height);

        Rect(Float32 (&array)[4]);

        Vector2 Position();

        Vector2 Size();
    };
}

#endif //CHOCO_CPP_RECT_H
