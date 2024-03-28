//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#ifndef CHOCO_CPP_GRAPHICS_H
#define CHOCO_CPP_GRAPHICS_H

#include "cc/linked_list.h"
#include "cc/drawable.h"

namespace CC {
    struct Graphics {
        void Draw(Drawable & drawable,
                  Int32 x,
                  Int32 y,
                  Int32 radians,
                  Int32 scaleX,
                  Int32 scaleY,
                  Int32 offsetX,
                  Int32 offsetY);
    };
}

#endif //CHOCO_CPP_GRAPHICS_H
