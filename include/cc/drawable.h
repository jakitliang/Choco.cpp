//
// Created by liangjie on 2024/4/11.
//

#ifndef CHOCO_CPP_DRAWABLE_H
#define CHOCO_CPP_DRAWABLE_H

namespace CC {
    struct Drawable {
        virtual void GetWidth() = 0;

        virtual void GetHeight() = 0;

        virtual void GetHandle() = 0;
    };
}

#endif //CHOCO_CPP_DRAWABLE_H
