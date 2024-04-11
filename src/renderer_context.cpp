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

CC::Renderer * CC::Renderer::Context::Open(void * windowHandle, CC::Int32 index, CC::UInt32 flags) {
    auto found = WindowsMap.find(windowHandle);
    if (found != WindowsMap.end()) return &found->second;

    Renderer renderer;
    renderer.Handle = SDL_CreateRenderer(static_cast<SDL_Window *>(windowHandle), index, flags);

    if (renderer.Handle == nullptr) return nullptr;

    RetainHandle(renderer.Handle);
    RendererMap[renderer.Handle] = windowHandle;
    WindowsMap[windowHandle] = std::move(renderer);

    return &WindowsMap[windowHandle];
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
