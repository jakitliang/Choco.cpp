//
// Created by liangjie on 2024/4/2.
//

#ifndef CHOCO_CPP_WINDOW_CONTEXT_H
#define CHOCO_CPP_WINDOW_CONTEXT_H

#include "cc/window.h"
#include <unordered_map>
#include <stack>

struct CC::Window::Context {
    using WindowMap = std::unordered_map<UInt32, Window>;
    using WindowStack = std::stack<Window *>;

    WindowMap Windows;
};

#endif //CHOCO_CPP_WINDOW_CONTEXT_H
