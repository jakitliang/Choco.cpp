//
// Created by liangjie on 2024/3/26.
//

#include "cc/render.h"
#include "cc/zone.h"
#include "SDL2/SDL.h"

const CC::UInt32 CC::Var<CC::RenderHandle>::Flags::Software      = SDL_RENDERER_SOFTWARE;
const CC::UInt32 CC::Var<CC::RenderHandle>::Flags::Hardware      = SDL_RENDERER_ACCELERATED;
const CC::UInt32 CC::Var<CC::RenderHandle>::Flags::PresentVSYNC  = SDL_RENDERER_PRESENTVSYNC;
const CC::UInt32 CC::Var<CC::RenderHandle>::Flags::TargetTexture = SDL_RENDERER_TARGETTEXTURE;

CC::Var<CC::RenderHandle>::Var() : handle(Make<RenderHandle>()) { handle->render = nullptr; }

CC::Var<CC::RenderHandle>::Var(const Var & var) : handle(Retain(var.handle)) {}

CC::Var<CC::RenderHandle>::Var(Var && var) : handle(var.handle) { var.handle = nullptr; }

CC::Var<CC::RenderHandle>::~Var() {
    Close();
    Destroy(handle);
}

bool CC::Var<CC::RenderHandle>::Open(CC::Window *wnd, CC::Int32 index, UInt32 flags) {
    if (handle->render != nullptr) return true;

    handle->render = SDL_CreateRenderer(static_cast<SDL_Window *>(wnd->handle->window), index, flags);

    return handle->render != nullptr;
}

void CC::Var<CC::RenderHandle>::Close() {
    if (handle->render == nullptr) return;

    SDL_DestroyRenderer(static_cast<SDL_Renderer *>(handle->render));
    handle->render = nullptr;
}
