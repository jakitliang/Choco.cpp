//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "window_context.h"
#include "cc/handle.h"
#include "SDL2/SDL.h"
#include <thread>
#include <stack>
#include <unordered_map>

CC::Window::Window() : Handle(nullptr) {}

CC::Window::Window(CC::Window && window) noexcept : Handle(window.Handle) { window.Handle = nullptr; }

CC::Window::~Window() {
    Close();
}

bool CC::Window::Open(const char * title,
                      Int32 x, Int32 y,
                      Int32 width, Int32 height,
                      UInt32 flags, UInt32 modes) {
    if (Handle) return true;

    Handle = Context::GetContext().Open(title, x, y, width, height, flags);
    Context::GetContext().Push(this);

//    Renderer renderer;

//    if (!renderer.Open(Handle, -1, modes)) {
//        SDL_DestroyWindow(static_cast<SDL_Window *>(Handle));
//        return false;
//    }


    return Handle != nullptr;
}

bool CC::Window::Open(void * windowHandle) {
    Handle = Context::GetContext().Open(windowHandle);
    return Handle != nullptr;
}

void CC::Window::Close() {
    if (Handle == nullptr) return;

    Context::GetContext().Close(Handle);
    Context::GetContext().Delete(this);
    Handle = nullptr;
}

CC::UInt32 CC::Window::GetID() {
    if (Handle == nullptr) return 0;
    return SDL_GetWindowID(static_cast<SDL_Window *>(Handle));
}

void CC::Window::on(CC::UInt32 event) {
    if (event == SDL_MOUSEBUTTONDOWN) {
//        if (Delegate)
    }
}

void CC::Window::Update(UInt64 deltaTime) {}

void CC::Window::Draw() {
//    SDL_RenderClear(renderer.get<SDL_Renderer>());
//
//    SDL_RenderPresent(renderer.get<SDL_Renderer>());
}

//CC::Renderer * CC::Window::GetRenderer() {
////    Renderer::Current();
//}

CC::Window &CC::Window::operator=(CC::Window &&window) noexcept {
    if (this == &window) return *this;

    Close();
    Handle = window.Handle;
    window.Handle = nullptr;

    return *this;
}

CC::Window * CC::Window::GetCurrent() {
    auto & windowStack = Context::GetContext().WindowStack;
    if (windowStack.Count() == 0) return nullptr;
    return windowStack.Last();
}

void CC::Window::SetCurrent(CC::Window * window) {
    auto & windowStack = Context::GetContext().WindowStack;
    for (auto & wnd : windowStack) {
        if (wnd->Handle == window->Handle) {
            Swap(wnd, windowStack.Last());
            break;
        }
    }
}
