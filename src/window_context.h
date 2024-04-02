//
// Created by liangjie on 2024/4/2.
//

#ifndef CHOCO_CPP_WINDOW_CONTEXT_H
#define CHOCO_CPP_WINDOW_CONTEXT_H

#include "cc/window.h"
#include <unordered_map>
#include <stack>

struct CC::Window::Context {
    using WindowMap = std::unordered_map<UInt32, CC::Window>;
    using WindowStack = std::stack<CC::Window *>;

    WindowMap Windows;
    WindowStack State;

    static Context & GetContext();
};

#endif //CHOCO_CPP_WINDOW_CONTEXT_H
