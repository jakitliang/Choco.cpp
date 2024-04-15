//
// Created by liangjie on 2024/4/15.
//

#include "cc/vertex.h"

CC::Vertex CC::Vertex::Zero() {
    return {Vector3::Zero(), Colors::Black, Vector2::Zero()};
}

CC::Vertex CC::Vertex::Zero(CC::Color color) {
    return {Vector3::Zero(), color, Vector2::Zero()};
}
