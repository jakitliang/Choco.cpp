//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#ifndef CHOCO_CPP_DRAWABLE_H
#define CHOCO_CPP_DRAWABLE_H

namespace CC {
    struct Drawable {
        virtual void draw(Int32 x,
                          Int32 y,
                          Int32 radians,
                          Int32 scaleX,
                          Int32 scaleY,
                          Int32 offsetX,
                          Int32 offsetY) = 0;
    };
}

#endif //CHOCO_CPP_DRAWABLE_H
