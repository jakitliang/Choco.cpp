//
// Created by liangjie on 2024/4/2.
//

#ifndef CHOCO_CPP_WINDOW_CONTEXT_H
#define CHOCO_CPP_WINDOW_CONTEXT_H

#include "cc/window.h"
#include <unordered_map>
#include <stack>

struct CC::Window::Context {
    using WindowMapType = std::unordered_map<UInt32, CC::Window>;
    using WindowHandleMapType = std::unordered_map<void *, UInt32>;
    using WindowStackType = std::stack<CC::Window *>;

    WindowMapType WindowsMap;
    WindowStackType WindowState;

    static Context & GetContext();

    static Window OpenWindow();

    static void CloseWindow();
};

#endif //CHOCO_CPP_WINDOW_CONTEXT_H
