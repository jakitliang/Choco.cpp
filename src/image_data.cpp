//
// Created by liangjie on 2024/4/1.
//

#include "cc/image_data.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

CC::ImageData::~ImageData() noexcept {
    Close();
}

bool CC::ImageData::Open(CC::UInt32 flags,
                         CC::Int32 width, CC::Int32 height,
                         CC::Int32 depth,
                         CC::UInt32 RMask, CC::UInt32 GMask, CC::UInt32 BMask, CC::UInt32 AMask) {
    auto & surface = get<SDL_Surface>();
    if (surface) return true;

    surface = SDL_CreateRGBSurface(flags,
                                   width, height,
                                   depth,
                                   RMask, GMask, BMask, AMask);
    return surface != nullptr;
}

bool CC::ImageData::Open(CC::UInt32 flags,
                         CC::Int32 width, CC::Int32 height,
                         CC::Int32 depth, CC::UInt32 format) {
    auto & surface = get<SDL_Surface>();
    if (surface) return true;

    surface = SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format);
    return surface != nullptr;
}

bool CC::ImageData::Open(void *pixels,
                         CC::Int32 width, CC::Int32 height,
                         CC::Int32 depth, CC::Int32 pitch,
                         CC::UInt32 RMask, CC::UInt32 GMask, CC::UInt32 BMask, CC::UInt32 AMask) {
    auto & surface = get<SDL_Surface>();
    if (surface) return true;

    surface = SDL_CreateRGBSurfaceFrom(pixels,
                                       width, height,
                                       depth, pitch,
                                       RMask, GMask, BMask, AMask);
    return surface != nullptr;
}

bool CC::ImageData::Open(void *pixels,
                         CC::Int32 width, CC::Int32 height,
                         CC::Int32 depth, CC::Int32 pitch,
                         CC::UInt32 format) {
    auto & surface = get<SDL_Surface>();
    if (surface) return true;

    surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, format);
    return surface != nullptr;
}

bool CC::ImageData::Open(const char *fileName) {
    auto & surface = get<SDL_Surface>();
    if (surface) return true;

    surface = IMG_Load(fileName);
    return surface != nullptr;
}

bool CC::ImageData::Open(const void *buffer, CC::Size size) {
    auto & surface = get<SDL_Surface>();
    if (surface) return true;

    surface = IMG_Load_RW(SDL_RWFromConstMem(buffer, size), 1);
    return surface != nullptr;
}

void CC::ImageData::Close() {
    auto & surface = get<SDL_Surface>();
    if (surface == nullptr) return;

    SDL_FreeSurface(surface);

    surface = nullptr;
}
