//
// Created by liangjie on 2024/4/16.
//

#include "cc/font.h"
#include "cc/handle.h"
#include "SDL2/SDL_ttf.h"

void FontFinalizer(void * handle) {}

CC::Font::Font() : Handle(nullptr) {
    if (TTF_WasInit()) return;

    TTF_Init();
}

CC::Font::Font(const CC::Font &font) : Handle(RetainHandle(font.Handle)) {}

CC::Font::~Font() {
    if (Handle == nullptr) return;

    Close();
}

bool CC::Font::Open(const char *name, CC::Size size) {
    if (Handle) return true;

    Handle = TTF_OpenFont(name, size);

    return Handle != nullptr;
}

bool CC::Font::Open(const CC::Byte *bytes, Size bytesLength, CC::Size size) {
    if (Handle) return true;

    auto rw = SDL_RWFromConstMem(bytes, bytesLength);

    Handle = TTF_OpenFontRW(rw, 0, size);

    return Handle != nullptr;
}

void CC::Font::Close() {
    if (Handle) return;

    ReleaseHandle(Handle, FontFinalizer);
    Handle = nullptr;
}

CC::Font &CC::Font::operator=(const CC::Font &font) {
    if (this == &font) return *this;

    Close();
    Handle = RetainHandle(font.Handle);

    return *this;
}
