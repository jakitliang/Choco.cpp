//
// Created by liangjie on 2024/3/26.
//

#include "cc/renderer.h"
#include "SDL2/SDL.h"

CC::Renderer::~Renderer() {
    Close();
}

bool CC::Renderer::Open(Handle * windowHandle, Int32 index, UInt32 flags) {
    auto & renderer = get<SDL_Renderer>();

    if (renderer) return true;

    renderer = SDL_CreateRenderer(windowHandle->get<SDL_Window>(), index, flags);

    return renderer != nullptr;
}

void CC::Renderer::Close() {
    auto & renderer = get<SDL_Renderer>();

    if (renderer == nullptr) return;

    SDL_DestroyRenderer(renderer);

    renderer = nullptr;
}
