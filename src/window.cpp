//
// Created by liangjie on 2024/3/26.
//

#include "cc/window.h"
#include "cc/zone.h"
#include "SDL2/SDL.h"
#include <thread>

namespace CC {
    const UInt32 Var<WindowHandle>::Flags::FullScreen = SDL_WINDOW_FULLSCREEN;
    const UInt32 Var<WindowHandle>::Flags::OpenGL = SDL_WINDOW_OPENGL;
    const UInt32 Var<WindowHandle>::Flags::Shown = SDL_WINDOW_SHOWN;
    const UInt32 Var<WindowHandle>::Flags::Hidden = SDL_WINDOW_HIDDEN;
    const UInt32 Var<WindowHandle>::Flags::Borderless = SDL_WINDOW_BORDERLESS;
    const UInt32 Var<WindowHandle>::Flags::Resizable = SDL_WINDOW_RESIZABLE;
    const UInt32 Var<WindowHandle>::Flags::Minimized = SDL_WINDOW_MINIMIZED;
    const UInt32 Var<WindowHandle>::Flags::Maximized = SDL_WINDOW_MAXIMIZED;
    const UInt32 Var<WindowHandle>::Flags::MouseGrabbed = SDL_WINDOW_MOUSE_GRABBED;
    const UInt32 Var<WindowHandle>::Flags::InputFocus = SDL_WINDOW_INPUT_FOCUS;
    const UInt32 Var<WindowHandle>::Flags::MouseFocus = SDL_WINDOW_MOUSE_FOCUS;
    const UInt32 Var<WindowHandle>::Flags::FullscreenDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP;
    const UInt32 Var<WindowHandle>::Flags::Foreign = SDL_WINDOW_FOREIGN;
    const UInt32 Var<WindowHandle>::Flags::AllowHDPI = SDL_WINDOW_ALLOW_HIGHDPI;
    const UInt32 Var<WindowHandle>::Flags::MouseCapture = SDL_WINDOW_MOUSE_CAPTURE;
    const UInt32 Var<WindowHandle>::Flags::AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP;
    const UInt32 Var<WindowHandle>::Flags::SkipTaskBar = SDL_WINDOW_SKIP_TASKBAR;
    const UInt32 Var<WindowHandle>::Flags::Utility = SDL_WINDOW_UTILITY;
    const UInt32 Var<WindowHandle>::Flags::Tooltip = SDL_WINDOW_TOOLTIP;
    const UInt32 Var<WindowHandle>::Flags::PopupMenu = SDL_WINDOW_POPUP_MENU;
    const UInt32 Var<WindowHandle>::Flags::KeyboardGrabbed = SDL_WINDOW_KEYBOARD_GRABBED;
    const UInt32 Var<WindowHandle>::Flags::Vulkan = SDL_WINDOW_VULKAN;
    const UInt32 Var<WindowHandle>::Flags::Metal = SDL_WINDOW_METAL;
    const UInt32 Var<WindowHandle>::Flags::InputGrabbed = SDL_WINDOW_INPUT_GRABBED;
}

CC::Var<CC::WindowHandle>::Var() : handle(Make<WindowHandle>()), renderer(Make<Renderer>()) {
    handle->window = nullptr;
}

CC::Var<CC::WindowHandle>::Var(const Var & window)
    : handle(Retain(window.handle)), renderer(Retain(window.renderer)) {}

CC::Var<CC::WindowHandle>::Var(Var && window)
    : handle(window.handle), renderer(window.renderer) {
    window.handle = nullptr;
    window.renderer = nullptr;
}

CC::Var<CC::WindowHandle>::~Var() {
    Close();
    Destroy(renderer);
    Destroy(handle);
}

bool CC::Var<CC::WindowHandle>::Open(const char * title,
                                     Int32 x, Int32 y,
                                     Int32 width, Int32 height,
                                     UInt32 flags, UInt32 modes) {
    if (handle->window != nullptr) return true;

    handle->window = SDL_CreateWindow(title, x, y, width, height, flags);

    if (handle->window == nullptr) return false;

    if (!renderer->Open(handle, -1, modes)) {
        SDL_DestroyWindow(static_cast<SDL_Window *>(handle->window));
        handle->window = nullptr;
    }

    return handle->window != nullptr;
}

void CC::Var<CC::WindowHandle>::Close() {
    if (handle->window == nullptr) return;

    renderer->Close();
    SDL_DestroyWindow(static_cast<SDL_Window *>(handle->window));

    handle->window = nullptr;
}

void CC::Var<CC::WindowHandle>::on(CC::UInt32 event) {
    if (event == SDL_MOUSEBUTTONDOWN) {
//        if (Delegate)
    }
}
