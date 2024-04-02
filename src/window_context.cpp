//
// Created by liangjie on 2024/4/2.
//

#include "window_context.h"

static CC::Window::Context WindowContext = {};

CC::Window::Context &CC::Window::Context::GetContext() {
    return WindowContext;
}
