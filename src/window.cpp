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
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    return window != nullptr;
}

void CC::Window::Close() {
    auto & window = get<SDL_Window>();

    if (window == nullptr) return;

    renderer.Close();
    SDL_DestroyWindow(window);

    window = nullptr;
}

void CC::Window::on(CC::UInt32 event) {
    if (event == SDL_MOUSEBUTTONDOWN) {
//        if (Delegate)
    }
}
