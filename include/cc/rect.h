//
// Created by liangjie on 2024/4/29.
//

#ifndef CHOCO_CPP_RECT_H
#define CHOCO_CPP_RECT_H

#include "cc/vertex.h"

namespace CC {
    struct Rect {
        Vertex Vertices[4];
        UInt32 Indices[6];

        void SetColor(Color color);

        void SetColor(Color topRight,
                      Color bottomRight,
                      Color bottomLeft,
                      Color topLeft);

        static Rect Make(Float32 x, Float32 y, Float32 width, Float32 height);
    };
}

#endif //CHOCO_CPP_RECT_H
