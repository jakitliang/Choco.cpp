//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/texture.h"
#include "SDL2/SDL.h"

CC::Texture::~Texture() {
    Close();
}

bool CC::Texture::Open(CC::Handle *rendererHandle,
                       CC::Int32 width, Int32 height,
                       CC::UInt32 format, CC::Int32 access) {
    auto & texture = get<SDL_Texture>();

    if (texture) return true;

    texture = SDL_CreateTexture(rendererHandle->get<SDL_Renderer>(), format, access, width, height);

    return texture != nullptr;
}

void CC::Texture::Close() {
    auto & texture = get<SDL_Texture>();

    if (texture == nullptr) return;

    SDL_DestroyTexture(texture);

    texture = nullptr;
}