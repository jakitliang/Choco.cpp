//
// Created by liangjie on 2024/4/1.
//

#include "cc/image.h"
#include "SDL2/SDL_image.h"

bool CC::Image::Open(Handle * rendererHandle, const char *fileName) {
    auto & texture = get<SDL_Texture>();
    if (texture != nullptr) return true;

    auto renderer = rendererHandle->get<SDL_Renderer>();
    auto surface = IMG_Load(fileName);

    if (surface == nullptr) return false;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture != nullptr;
}

bool CC::Image::Open(CC::Handle * rendererHandle, const void * buffer, CC::Size size) {
    auto & texture = get<SDL_Texture>();
    if (texture != nullptr) return true;

    auto surface = IMG_Load_RW(SDL_RWFromConstMem(buffer, size), 1);

    if (surface == nullptr) return false;

    texture = SDL_CreateTextureFromSurface(rendererHandle->get<SDL_Renderer>(), surface);
    SDL_FreeSurface(surface);

    return texture != nullptr;
}

bool CC::Image::Open(CC::Handle * rendererHandle, CC::Handle *imageData) {
    auto & texture = get<SDL_Texture>();
    if (texture != nullptr) return true;

    texture = SDL_CreateTextureFromSurface(
            rendererHandle->get<SDL_Renderer>(), imageData->get<SDL_Surface>());

    return texture != nullptr;
}

void CC::Image::Close() {
    auto & texture = get<SDL_Texture>();
    if (texture == nullptr) return;

    SDL_DestroyTexture(texture);
    texture = nullptr;
}
