//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/handle.h"
#include "cc/renderer.h"
#include "cc/image_data.h"
#include "cc/texture.h"
#include "SDL2/SDL.h"

void TextureHandleFinalizer(void * handle) {
    SDL_DestroyTexture(static_cast<SDL_Texture *>(handle));
}

CC::Texture::Texture() : Handle(nullptr) {}

CC::Texture::Texture(const CC::Texture &texture) : Handle(RetainHandle(texture.Handle)) {}

CC::Texture::Texture(CC::Texture &&texture) noexcept {}

CC::Texture::~Texture() {
    if (Handle == nullptr) return;

    Close();
}

bool CC::Texture::Open(Renderer * renderer,
                       CC::Int32 width, Int32 height,
                       CC::UInt32 format, CC::Int32 access) {
    Handle = SDL_CreateTexture(static_cast<SDL_Renderer *>(renderer->Handle), format, access, width, height);
    Handle = RetainHandle(Handle);
    return Handle != nullptr;
}

bool CC::Texture::Open(Renderer * renderer, ImageData * imageData) {
    Handle = SDL_CreateTextureFromSurface(static_cast<SDL_Renderer *>(renderer->Handle),
                                          static_cast<SDL_Surface *>(imageData->Handle));
    Handle = RetainHandle(Handle);
    return Handle != nullptr;
}

void CC::Texture::Close() {
    if (Handle == nullptr) return;

    ReleaseHandle(Handle, TextureHandleFinalizer);

    Handle = nullptr;
}

CC::Texture &CC::Texture::operator=(const CC::Texture &texture) {
    if (this == &texture) return *this;

    Close();
    Handle = RetainHandle(texture.Handle);

    return *this;
}

CC::Texture &CC::Texture::operator=(CC::Texture &&texture) noexcept {
    if (this == &texture) return *this;

    Close();
    Handle = texture.Handle;
    texture.Handle = nullptr;

    return *this;
}