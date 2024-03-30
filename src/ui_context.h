//
// Created by Jakit on 2024/3/30.
//

#ifndef CHOCO_CPP_UI_CONTEXT_H
#define CHOCO_CPP_UI_CONTEXT_H

#include "cc/window.h"
#include <stack>

namespace CC {
    struct UIContext {
        std::stack<Window *> windows;

        static UIContext & GetContext();
    };
}

#endif //CHOCO_CPP_UI_CONTEXT_H
