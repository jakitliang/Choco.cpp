//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/renderer.h"
#include "cc/canvas.h"
#include "cc/handle.h"
#include <SDL2/SDL.h>

void CanvasHandleFinalize(void * handle) {
    SDL_DestroyTexture(static_cast<SDL_Texture *>(handle));
}

CC::Canvas::Canvas() : Handle(nullptr) {}

CC::Canvas::Canvas(const CC::Canvas &render) : Handle(RetainHandle(render.Handle)) {}

CC::Canvas::Canvas(CC::Canvas &&render) : Handle(render.Handle) { render.Handle = nullptr; }

CC::Canvas::~Canvas() {
    if (Handle == nullptr) return;

    Close();
}

bool CC::Canvas::Open(CC::Renderer *renderer, CC::Int32 width, CC::Int32 height, CC::UInt32 format, CC::Int32 access) {
    Handle = SDL_CreateTexture(static_cast<SDL_Renderer *>(renderer->Handle), format, access, width, height);
    Handle = RetainHandle(Handle);
    return Handle != nullptr;
}

void CC::Canvas::Close() {
    if (Handle == nullptr) return;

    ReleaseHandle(Handle, CanvasHandleFinalize);

    Handle = nullptr;
}

CC::Canvas &CC::Canvas::operator=(const CC::Canvas &canvas) {
    if (this == &canvas) return *this;

    Close();
    Handle = RetainHandle(canvas.Handle);

    return *this;
}

CC::Canvas &CC::Canvas::operator=(CC::Canvas &&canvas) {
    if (this == &canvas) return *this;

    Close();
    Handle = canvas.Handle;
    canvas.Handle = nullptr;

    return *this;
}
