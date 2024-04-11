//
// Created by liangjie on 2024/4/1.
//

#include "cc/image_data.h"
#include "cc/handle.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

void ImageDataHandleFinalizer(void * handle) {
    SDL_FreeSurface(static_cast<SDL_Surface *>(handle));
}

CC::ImageData::ImageData() : Handle(nullptr) {}

CC::ImageData::ImageData(const CC::ImageData &imageData) : Handle(RetainHandle(imageData.Handle)) {}

CC::ImageData::ImageData(CC::ImageData &&imageData) noexcept : Handle(imageData.Handle) { imageData.Handle = nullptr; }

CC::ImageData::~ImageData() {
    if (Handle == nullptr) return;

    Close();
}

bool CC::ImageData::Open(CC::UInt32 flags,
                         CC::Int32 width, CC::Int32 height,
                         CC::Int32 depth,
                         CC::UInt32 RMask, CC::UInt32 GMask, CC::UInt32 BMask, CC::UInt32 AMask) {
    if (Handle) return true;

    Handle = SDL_CreateRGBSurface(flags,
                                   width, height,
                                   depth,
                                   RMask, GMask, BMask, AMask);
    return Handle != nullptr;
}

bool CC::ImageData::Open(CC::UInt32 flags,
                         CC::Int32 width, CC::Int32 height,
                         CC::Int32 depth, CC::UInt32 format) {
    if (Handle) return true;

    Handle = SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format);
    return Handle != nullptr;
}

bool CC::ImageData::Open(void *pixels,
                         CC::Int32 width, CC::Int32 height,
                         CC::Int32 depth, CC::Int32 pitch,
                         CC::UInt32 RMask, CC::UInt32 GMask, CC::UInt32 BMask, CC::UInt32 AMask) {
    if (Handle) return true;

    Handle = SDL_CreateRGBSurfaceFrom(pixels,
                                       width, height,
                                       depth, pitch,
                                       RMask, GMask, BMask, AMask);
    return Handle != nullptr;
}

bool CC::ImageData::Open(void *pixels,
                         CC::Int32 width, CC::Int32 height,
                         CC::Int32 depth, CC::Int32 pitch,
                         CC::UInt32 format) {
    if (Handle) return true;

    Handle = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, format);
    return Handle != nullptr;
}

bool CC::ImageData::Open(const char *fileName) {
    if (Handle) return true;

    Handle = IMG_Load(fileName);
    return Handle != nullptr;
}

bool CC::ImageData::Open(const void *buffer, CC::Size size) {
    if (Handle) return true;

    Handle = IMG_Load_RW(SDL_RWFromConstMem(buffer, size), 1);
    return Handle != nullptr;
}

void CC::ImageData::Close() {
    if (Handle == nullptr) return;

    ReleaseHandle(Handle, ImageDataHandleFinalizer);

    Handle = nullptr;
}

CC::ImageData &CC::ImageData::operator=(const CC::ImageData &imageData) {
    if (this == &imageData) return *this;

    Close();
    Handle = RetainHandle(imageData.Handle);

    return *this;
}

CC::ImageData &CC::ImageData::operator=(CC::ImageData &&imageData) {
    if (this == &imageData) return *this;

    Close();
    Handle = imageData.Handle;
    imageData.Handle = nullptr;

    return *this;
}
