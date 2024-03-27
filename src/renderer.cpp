//
// Created by liangjie on 2024/3/26.
//

#include "cc/renderer.h"
#include "cc/zone.h"
#include "SDL2/SDL.h"

namespace CC {
    const UInt32 Renderer::Flags::Software      = SDL_RENDERER_SOFTWARE;
    const UInt32 Renderer::Flags::Hardware      = SDL_RENDERER_ACCELERATED;
    const UInt32 Renderer::Flags::PresentVSYNC  = SDL_RENDERER_PRESENTVSYNC;
    const UInt32 Renderer::Flags::TargetTexture = SDL_RENDERER_TARGETTEXTURE;
}

CC::Var<CC::RendererHandle>::Var() : handle(Make<RendererHandle>()) {}

CC::Var<CC::RendererHandle>::Var(const Var & renderer) : handle(Retain(renderer.handle)) {}

CC::Var<CC::RendererHandle>::Var(Var && renderer) : handle(renderer.handle) {
    renderer.handle = nullptr;
}

CC::Var<CC::RendererHandle>::~Var() {
    Close();
}

bool CC::Var<CC::RendererHandle>::Open(WindowHandle * windowHandle, Int32 index, UInt32 flags) {
    if (handle->renderer) return true;

    handle->renderer = SDL_CreateRenderer(static_cast<SDL_Window *>(windowHandle->window), index, flags);

    return handle->renderer != nullptr;
}

void CC::Var<CC::RendererHandle>::Close() {
    if (handle->renderer == nullptr) return;

    SDL_DestroyRenderer(static_cast<SDL_Renderer *>(handle->renderer));

    handle->renderer = nullptr;
}
