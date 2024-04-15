//
// Created by liangjie on 2024/4/15.
//

#ifndef CHOCO_CPP_COLOR_H
#define CHOCO_CPP_COLOR_H

#include "cc/types.h"

namespace CC {
    struct Color {
        UInt8 Red;
        UInt8 Green;
        UInt8 Blue;
        UInt8 Alpha;
    };

    struct Colors {
        static const Color Black;
        static const Color Gray;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color White;
    };
}

#endif //CHOCO_CPP_COLOR_H
