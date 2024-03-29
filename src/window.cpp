//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "cc/renderer.h"
#include "cc/zone.h"
#include "SDL2/SDL.h"
#include <thread>

CC::Window::~Window() {
    Close();
}

bool CC::Window::Open(const char * title,
                      Int32 x, Int32 y,
                      Int32 width, Int32 height,
                      UInt32 flags, UInt32 modes) {
    auto & window = get<SDL_Window>();

    if (window) return true;

    window = SDL_CreateWindow(title, x, y, width, height, flags);

    if (window == nullptr) return false;

    if (!renderer.Open(this, -1, modes)) {
        return false;
    }

    if (!layer.Open(&renderer, width, height, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET)) {
        return false;
    }

    return true;
}

void CC::Window::Close() {
    auto & window = get<SDL_Window>();

    if (window == nullptr) return;

    layer.Close();
    renderer.Close();
    SDL_DestroyWindow(window);

    if (subWindows.Count()) {
        for (auto & w : subWindows) {
            w.Close();
        }
    }

    window = nullptr;
}

void CC::Window::on(CC::UInt32 event) {
    if (event == SDL_MOUSEBUTTONDOWN) {
//        if (Delegate)
    }
}

void CC::Window::Update(UInt64 deltaTime) {}

void CC::Window::Draw() {}
