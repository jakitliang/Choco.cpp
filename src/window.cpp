//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "window_context.h"
//#include "cc/renderer.h"
#include "cc/handle.h"
#include "SDL2/SDL.h"
#include <thread>
#include <stack>
#include <unordered_map>

void Finalizer(void * handle) {
    SDL_DestroyWindow(static_cast<SDL_Window *>(handle));
}

CC::Window::Window() : Handle(nullptr) {}

CC::Window::Window(const CC::Window &window) : Handle(RetainHandle(window.Handle)) {}

CC::Window::Window(CC::Window &&window) : Handle(window.Handle) { window.Handle = nullptr; }

CC::Window::~Window() {
    if (Handle == nullptr) return;

    ReleaseHandle(Handle, Finalizer);
}

CC::UInt32 CC::Window::Open(const char * title,
                      Int32 x, Int32 y,
                      Int32 width, Int32 height,
                      UInt32 flags, UInt32 modes) {
    if (Handle) return GetID();

    Handle = SDL_CreateWindow(title, x, y, width, height, flags);

    if (Handle == nullptr) return 0;

//    Renderer renderer;

//    if (!renderer.Open(Handle, -1, modes)) {
//        SDL_DestroyWindow(static_cast<SDL_Window *>(Handle));
//        return false;
//    }

    RetainHandle(Handle);
    Context::GetContext().Windows[GetID()] = *this;

    return GetID();
}

void CC::Window::Close() {
    if (Handle == nullptr) return;

    Context::GetContext().Windows.erase(GetID());
    ReleaseHandle(Handle, Finalizer);
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

CC::Window &CC::Window::operator=(const CC::Window &window) {
    if (this == &window) return *this;

    ReleaseHandle(Handle, Finalizer);
    Handle = RetainHandle(window.Handle);
    return *this;
}

CC::Window &CC::Window::operator=(CC::Window &&window) noexcept {
    ReleaseHandle(Handle, Finalizer);
    Handle = window.Handle;
    window.Handle = nullptr;

    return *this;
}

CC::Window * CC::Window::Current() {
    return Context::GetContext().State.top();
}
