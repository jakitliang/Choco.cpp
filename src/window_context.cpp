//
// Created by liangjie on 2024/4/2.
//

#include "window_context.h"
#include "cc/handle.h"
#include "SDL2/SDL.h"

static CC::Window::Context WindowContext = {};

void WindowHandleFinalizer(void * handle) {
    SDL_DestroyWindow(static_cast<SDL_Window *>(handle));
}

void * CC::Window::Context::Open(const char * title,
                                 Int32 x, Int32 y,
                                 Int32 width, Int32 height,
                                 UInt32 flags) {
    auto handle = SDL_CreateWindow(title, x, y, width, height, flags);

    if (handle != nullptr) {
        RetainHandle(handle);
        WindowsMap[handle] = SDL_GetWindowID(handle);
    }

    return handle;
}

void * CC::Window::Context::Open(void *handle) {
    if (handle == nullptr) return nullptr;

    if (WindowsMap.find(handle) == WindowsMap.end()) return nullptr;

    return RetainHandle(handle);
}

void CC::Window::Context::Close(void * handle) {
    if (handle == nullptr) return;

    if (WindowsMap.find(handle) == WindowsMap.end()) return;

    if (ReleaseHandle(handle, WindowHandleFinalizer)) WindowsMap.erase(handle);
}

void CC::Window::Context::Push(CC::Window * window) {
    if (std::find(WindowStack.begin(), WindowStack.end(), window) != WindowStack.end()) return;

    WindowStack.Push(window);
};

void CC::Window::Context::Delete(CC::Window * window) {
    if (std::find(WindowStack.begin(), WindowStack.end(), window) == WindowStack.end()) return;

    int index = 0;
    for (auto & wnd : WindowStack) {
        if (wnd->Handle == window->Handle) {
            WindowStack.Delete(index);
            break;
        }

        index += 1;
    }
}

CC::Window::Context &CC::Window::Context::GetContext() {
    return WindowContext;
}
