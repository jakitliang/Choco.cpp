//
// Created by liangjie on 2024/4/2.
//

#ifndef CHOCO_CPP_WINDOW_CONTEXT_H
#define CHOCO_CPP_WINDOW_CONTEXT_H

#include "cc/window.h"
#include "cc/linked_list.h"
#include <unordered_map>

struct CC::Window::Context {
    using WindowMapType = std::unordered_map<void *, UInt32>;
    using WindowStackType = LinkedList<CC::Window *>;
    using WindowStateType = Linked<CC::Window *>::Iterator;

    WindowMapType WindowsMap;
    WindowStackType WindowStack;
    WindowStateType WindowState;

    void * Open(const char * title,
                Int32 x, Int32 y,
                Int32 width, Int32 height,
                UInt32 flags);

    void * Open(void * handle);

    void Close(void * handle);

    void Push(Window * window);

    void Delete(Window * window);

    Linked<CC::Window *>::Iterator begin();

    Linked<CC::Window *>::Iterator end();

    static Context & GetContext();
};

#endif //CHOCO_CPP_WINDOW_CONTEXT_H
