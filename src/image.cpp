//
// Created by liangjie on 2024/4/1.
//

#include "cc/image.h"
#include "cc/handle.h"
#include "cc/renderer.h"
#include "cc/image_data.h"
#include "SDL2/SDL_image.h"

void ImageHandleFinalizer(void * handle) {
    SDL_DestroyTexture(static_cast<SDL_Texture *>(handle));
}

CC::Image::Image() : Handle(nullptr) {}

CC::Image::Image(const CC::Image &image) : Handle(RetainHandle(image.Handle)) {}

CC::Image::Image(CC::Image &&image) : Handle(image.Handle) { image.Handle = nullptr; }

CC::Image::~Image() {
    if (Handle == nullptr) return;

    Close();
}

bool CC::Image::Open(CC::Renderer * renderer, const char *fileName) {
    if (Handle != nullptr) return true;

    auto surface = IMG_Load(fileName);

    if (surface == nullptr) return false;

    Handle = SDL_CreateTextureFromSurface(static_cast<SDL_Renderer *>(renderer->Handle), surface);
    Handle = RetainHandle(Handle);

    SDL_FreeSurface(surface);

    return Handle != nullptr;
}

bool CC::Image::Open(CC::Renderer * renderer, const void * buffer, CC::Size size) {
    if (Handle != nullptr) return true;

    auto surface = IMG_Load_RW(SDL_RWFromConstMem(buffer, size), 1);

    if (surface == nullptr) return false;

    Handle = SDL_CreateTextureFromSurface(static_cast<SDL_Renderer *>(renderer->Handle), surface);
    Handle = RetainHandle(Handle);

    SDL_FreeSurface(surface);

    return Handle != nullptr;
}

bool CC::Image::Open(CC::Renderer * renderer, CC::ImageData * imageData) {
    if (Handle != nullptr) return true;

    Handle = SDL_CreateTextureFromSurface(
            static_cast<SDL_Renderer *>(renderer->Handle),
            static_cast<SDL_Surface *>(imageData->Handle));
    Handle = RetainHandle(Handle);

    return Handle != nullptr;
}

void CC::Image::Close() {
    if (Handle == nullptr) return;

    ReleaseHandle(Handle, ImageHandleFinalizer);

    Handle = nullptr;
}

void *CC::Image::GetHandle() {
    return Handle;
}

CC::Image &CC::Image::operator=(const CC::Image &image) {
    if (this == &image) return *this;

    Close();
    Handle = RetainHandle(image.Handle);

    return *this;
}

CC::Image &CC::Image::operator=(CC::Image &&image) {
    if (this == &image) return *this;

    Close();
    Handle = image.Handle;
    image.Handle = nullptr;

    return *this;
}
