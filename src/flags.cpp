//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/flags.h"
#include "SDL2/SDL.h"

namespace CC::Flags {
    // RendererHandle
    const UInt32 Renderer::Software      = SDL_RENDERER_SOFTWARE;
    const UInt32 Renderer::Hardware      = SDL_RENDERER_ACCELERATED;
    const UInt32 Renderer::PresentVSYNC  = SDL_RENDERER_PRESENTVSYNC;
    const UInt32 Renderer::TargetTexture = SDL_RENDERER_TARGETTEXTURE;

    // WindowHandle
    const UInt32 Window::FullScreen = SDL_WINDOW_FULLSCREEN;
    const UInt32 Window::OpenGL = SDL_WINDOW_OPENGL;
    const UInt32 Window::Shown = SDL_WINDOW_SHOWN;
    const UInt32 Window::Hidden = SDL_WINDOW_HIDDEN;
    const UInt32 Window::Borderless = SDL_WINDOW_BORDERLESS;
    const UInt32 Window::Resizable = SDL_WINDOW_RESIZABLE;
    const UInt32 Window::Minimized = SDL_WINDOW_MINIMIZED;
    const UInt32 Window::Maximized = SDL_WINDOW_MAXIMIZED;
    const UInt32 Window::MouseGrabbed = SDL_WINDOW_MOUSE_GRABBED;
    const UInt32 Window::InputFocus = SDL_WINDOW_INPUT_FOCUS;
    const UInt32 Window::MouseFocus = SDL_WINDOW_MOUSE_FOCUS;
    const UInt32 Window::FullscreenDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP;
    const UInt32 Window::Foreign = SDL_WINDOW_FOREIGN;
    const UInt32 Window::AllowHDPI = SDL_WINDOW_ALLOW_HIGHDPI;
    const UInt32 Window::MouseCapture = SDL_WINDOW_MOUSE_CAPTURE;
    const UInt32 Window::AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP;
    const UInt32 Window::SkipTaskBar = SDL_WINDOW_SKIP_TASKBAR;
    const UInt32 Window::Utility = SDL_WINDOW_UTILITY;
    const UInt32 Window::Tooltip = SDL_WINDOW_TOOLTIP;
    const UInt32 Window::PopupMenu = SDL_WINDOW_POPUP_MENU;
    const UInt32 Window::KeyboardGrabbed = SDL_WINDOW_KEYBOARD_GRABBED;
    const UInt32 Window::Vulkan = SDL_WINDOW_VULKAN;
    const UInt32 Window::Metal = SDL_WINDOW_METAL;
    const UInt32 Window::InputGrabbed = SDL_WINDOW_INPUT_GRABBED;
}
