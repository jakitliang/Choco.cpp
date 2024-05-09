//
// Created by liangjie on 2024/4/29.
//

#include "cc/rect.h"

void CC::Rect::SetColor(CC::Color color) {
    for (auto &vertex: Vertices) {
        vertex.Color = color;
    }
}

void CC::Rect::SetColor(CC::Color topRight, CC::Color bottomRight, CC::Color bottomLeft, CC::Color topLeft) {
    Vertices[0].Color = topRight;
    Vertices[1].Color = bottomRight;
    Vertices[2].Color = bottomLeft;
    Vertices[3].Color = topLeft;
}

CC::Rect CC::Rect::Make(CC::Float32 x, CC::Float32 y, CC::Float32 width, CC::Float32 height) {
    CC::Rect ret = {
        {
            { // top right
                {x + width, y, 0},
                {0, 0, 0, 1},
                {0, 0}
            },
            { // bottom right
                {x + width, y - height, 0},
                {0, 0, 0, 1},
                {0, 0}
            },
            { // bottom left
                {x, y - height, 0},
                {0, 0, 0, 1},
                {0, 0}
            },
            { // top left
                {x, y, 0},
                {0, 0, 0, 1},
                {0, 0}
            }
        },
        {0, 1, 3, 1, 2, 3}
    };

    return ret;
}
