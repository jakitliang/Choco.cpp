//
// Created by liangjie on 2024/3/26.
//

#ifndef CHOCO_CPP_WINDOW_H
#define CHOCO_CPP_WINDOW_H

#include "cc/types.h"

namespace CC {
    struct Window {
        void * handle;

        Window();

        Window(const Window & window);

        Window(Window && window);

        ~Window();
    };
}

#endif //CHOCO_CPP_WINDOW_H
