//
// Created by Jakit on 2024/3/28.
//

#ifndef CHOCO_CPP_SCREEN_H
#define CHOCO_CPP_SCREEN_H

#include "cc/types.h"

namespace CC {
    struct Screen {
        Int32 width;
        Int32 height;

        Screen();

        explicit Screen(Int32 index);
    };
}

#endif //CHOCO_CPP_SCREEN_H
