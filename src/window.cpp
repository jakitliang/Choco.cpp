//
// Created by liangjie on 2024/3/26.
//

#include "cc/window.h"
#include "cc/zone.h"
#include "SDL2/SDL.h"

const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::FullScreen = SDL_WINDOW_FULLSCREEN;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::OpenGL = SDL_WINDOW_OPENGL;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Shown = SDL_WINDOW_SHOWN;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Hidden = SDL_WINDOW_HIDDEN;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Borderless = SDL_WINDOW_BORDERLESS;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Resizable = SDL_WINDOW_RESIZABLE;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Minimized = SDL_WINDOW_MINIMIZED;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Maximized = SDL_WINDOW_MAXIMIZED;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::MouseGrabbed = SDL_WINDOW_MOUSE_GRABBED;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::InputFocus = SDL_WINDOW_INPUT_FOCUS;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::MouseFocus = SDL_WINDOW_MOUSE_FOCUS;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::FullscreenDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Foreign = SDL_WINDOW_FOREIGN;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::AllowHDPI = SDL_WINDOW_ALLOW_HIGHDPI;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::MouseCapture = SDL_WINDOW_MOUSE_CAPTURE;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::SkipTaskBar = SDL_WINDOW_SKIP_TASKBAR;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Utility = SDL_WINDOW_UTILITY;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Tooltip = SDL_WINDOW_TOOLTIP;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::PopupMenu = SDL_WINDOW_POPUP_MENU;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::KeyboardGrabbed = SDL_WINDOW_KEYBOARD_GRABBED;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Vulkan = SDL_WINDOW_VULKAN;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::Metal = SDL_WINDOW_METAL;
const CC::UInt32 CC::Var<CC::WindowHandle>::Flags::InputGrabbed = SDL_WINDOW_INPUT_GRABBED;

CC::Var<CC::WindowHandle>::Var() : handle(Make<WindowHandle>()) { handle->window = nullptr; }

CC::Var<CC::WindowHandle>::Var(const Var & var) : handle(Retain(var.handle)) {}

CC::Var<CC::WindowHandle>::Var(Var && var) : handle(var.handle) { var.handle = nullptr; }

CC::Var<CC::WindowHandle>::~Var() {
    Close();
    Destroy(handle);
}

bool CC::Var<CC::WindowHandle>::Open(const char *title,
                      CC::Int32 x,
                      CC::Int32 y,
                      CC::Int32 width,
                      CC::Int32 height,
                                     UInt32 flags) {
    if (handle->window != nullptr) return true;

    handle->window = SDL_CreateWindow(title, x, y, width, height, flags);

    return handle->window != nullptr;
}

void CC::Var<CC::WindowHandle>::Close() {
    if (handle->window == nullptr) return;

    SDL_DestroyWindow(static_cast<SDL_Window *>(handle->window));

    handle->window = nullptr;
}
