//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "cc/renderer.h"
#include "cc/zone.h"
#include "ui_context.h"
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
        return false;
    }

    UIContext::GetContext().Windows[GetID()] = *this;

    return true;
}

void CC::Window::Close() {
    auto & window = get<SDL_Window>();

    if (window == nullptr) return;

//    layer.Close();
    UIContext::GetContext().Windows.erase(GetID());
    renderer.Close();
    SDL_DestroyWindow(window);

//    if (subWindows.Count()) {
//        for (auto & w : subWindows) {
//            w.Close();
//        }
//    }

    window = nullptr;
}

CC::UInt32 CC::Window::GetID() {
    auto & window = get<SDL_Window>();
    return SDL_GetWindowID(window);
}

void CC::Window::on(CC::UInt32 event) {
    if (event == SDL_MOUSEBUTTONDOWN) {
//        if (Delegate)
    }
}

void CC::Window::Update(UInt64 deltaTime) {}

void CC::Window::Draw() {
    SDL_RenderClear(renderer.get<SDL_Renderer>());

    SDL_RenderPresent(renderer.get<SDL_Renderer>());
}
