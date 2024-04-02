//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "cc/renderer.h"
#include "cc/zone.h"
#include "SDL2/SDL.h"
#include <thread>
#include <stack>

struct CC::Window::Context {
    using WindowMap = std::unordered_map<UInt32, CC::Window>;
    using WindowStack = std::stack<CC::Window *>;

    WindowMap Windows;
    WindowStack State;
};

static CC::Window::Context WindowContext = {};

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

    Renderer renderer;

    if (!renderer.Open(this, -1, modes)) {
        SDL_DestroyWindow(window);
        return false;
    }

    WindowContext.Windows[GetID()] = *this;

    return true;
}

void CC::Window::Close() {
    auto & window = get<SDL_Window>();

    if (window == nullptr) return;

    auto id = GetID();
    auto renderer = WindowContext.Renderers[id];

    renderer.Close();
    SDL_DestroyWindow(window);
    window = nullptr;

    WindowContext.Windows.erase(id);
    WindowContext.Renderers.erase(id);
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

CC::Renderer * CC::Window::GetRenderer() {
    Renderer::Current();
}

CC::Window * CC::Window::Current() {
    return WindowContext.State.top();
}
