//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "window_context.h"
#include "cc/renderer.h"
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

    if (!Renderer::Open(Handle, -1, modes)) {
        Context::GetContext().Close(Handle);
        Context::GetContext().Delete(this);
        Handle = nullptr;
    }

    if (Handle != nullptr) onOpen();

    return Handle != nullptr;
}

bool CC::Window::Open(void * windowHandle) {
    Handle = Context::GetContext().Open(windowHandle);
    return Handle != nullptr;
}

void CC::Window::Close() {
    if (Handle == nullptr) return;

    onClose();

    Renderer::GetWithWindow(this)->Close();
    Context::GetContext().Close(Handle);
    Context::GetContext().Delete(this);

    Handle = nullptr;
}

CC::UInt32 CC::Window::GetID() {
    if (Handle == nullptr) return 0;
    return SDL_GetWindowID(static_cast<SDL_Window *>(Handle));
}

void CC::Window::onEvent(CC::UIEvent & event) {
    if (event.Type == SDL_WINDOWEVENT) {
        onStateChanged(event.window);

    } else if (event.Type < SDL_MOUSEMOTION) {
        if (event.Type == SDL_KEYDOWN || event.Type == SDL_KEYUP) {
            onKey(event.key);
        }

    } else if (event.Type < SDL_JOYAXISMOTION) {
        if (event.Type == SDL_MOUSEMOTION) {
            onMouseMotion(event.motion);

        } else if (event.Type == SDL_MOUSEBUTTONUP || event.Type == SDL_MOUSEBUTTONDOWN) {
            onMouseButton(event.button);

        } else if (event.Type == SDL_MOUSEWHEEL) {
            onMouseWheel(event.wheel);
        }
    }
}

void CC::Window::onStateChanged(CC::UIWindowEvent &event) {}

void CC::Window::onKey(CC::UIKeyboardEvent &event) {}

void CC::Window::onMouseMotion(CC::UIMouseMotionEvent &event) {}

void CC::Window::onMouseButton(CC::UIMouseButtonEvent &event) {}

void CC::Window::onMouseWheel(CC::UIMouseWheelEvent &event) {}

void CC::Window::onOpen() {}

void CC::Window::onClose() {}

void CC::Window::Update(UInt64 deltaTime) {}

void CC::Window::Draw() {
//    SDL_RenderClear(renderer.get<SDL_Renderer>());
//
//    SDL_RenderPresent(renderer.get<SDL_Renderer>());
}

void CC::Window::SetTransparent(Byte opacity) {
#ifdef _WINDOWS
    // Makes a window transparent by setting a transparency color.
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
    SDL_GetWindowWMInfo(window, &wmInfo);
    HWND hWnd = wmInfo.info.win.window;

    // Change window type to layered
    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Set transparency color
    SetLayeredWindowAttributes(hWnd, 0, opacity, LWA_ALPHA);
#endif
}

CC::Window &CC::Window::operator=(CC::Window &&window) noexcept {
    if (this == &window) return *this;

    Close();
    Handle = window.Handle;
    window.Handle = nullptr;

    return *this;
}

CC::Window * CC::Window::Current() {
    return *Context::GetContext().WindowState;
}
