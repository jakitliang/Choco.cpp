//
// Created by liangjie on 2024/4/3.
//

#include "renderer_context.h"
#include "cc/handle.h"
#include "SDL2/SDL.h"

static CC::Renderer::Context RendererContext = {};

void RendererHandleFinalizer(void * handle) {
    SDL_DestroyRenderer(static_cast<SDL_Renderer *>(handle));
}

void *CC::Renderer::Context::Open(CC::Renderer & renderer, void *windowHandle, CC::Int32 index, CC::UInt32 flags) {
    if (WindowsMap.find(windowHandle) != WindowsMap.end()) return nullptr;

    auto handle = SDL_CreateRenderer(static_cast<SDL_Window *>(windowHandle), index, flags);

    if (handle != nullptr) {
        RetainHandle(handle);
        RendererMap[handle] = windowHandle;
        WindowsMap[windowHandle] = std::move(renderer);
    }

    return handle;
}

void CC::Renderer::Context::Close(void *handle) {
    if (handle == nullptr) return;

    if (RendererMap.find(handle) == RendererMap.end()) return;

    if (ReleaseHandle(handle, RendererHandleFinalizer)) {
        WindowsMap.erase(RendererMap[handle]);
        RendererMap.erase(handle);
    }
}

CC::Renderer::Context & CC::Renderer::Context::GetContext() {
    return RendererContext;
}
