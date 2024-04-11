//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/texture.h"
#include "SDL2/SDL.h"

CC::Float32 CC::Texture::GetWidth() {
    return GetSize().X;
}

CC::Float32 CC::Texture::GetHeight() {
    return GetSize().Y;
}

CC::Vector2 CC::Texture::GetSize() {
    UInt32 format;
    Int32 access;
    Int32 width;
    Int32 height;

    SDL_QueryTexture(static_cast<SDL_Texture *>(GetHandle()), &format, &access, &width, &height);

    return {static_cast<Float32>(width), static_cast<Float32>(height)};
}
