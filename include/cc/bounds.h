//
// Created by liangjie on 2024/4/1.
//

#ifndef CHOCO_CPP_BOUNDS_H
#define CHOCO_CPP_BOUNDS_H

#include "cc/vector2.h"
#include "cc/vector3.h"

namespace CC {
    struct Bounds {
        union {
            Vector3 Center, Position;
        };
        Vector3 Size;
    };
}

#endif //CHOCO_CPP_BOUNDS_H
