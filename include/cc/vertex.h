//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/4/15.
//

#ifndef CHOCO_CPP_VERTEX_H
#define CHOCO_CPP_VERTEX_H

#include "cc/vector2.h"
#include "cc/vector3.h"
#include "cc/color.h"

namespace CC {
    struct Vertex {
        CC::Vector3 Position;
        CC::Color Color;
        CC::Vector2 UV;

        static Vertex Zero();

        static Vertex Zero(CC::Color color);
    };
}

#endif //CHOCO_CPP_VERTEX_H
