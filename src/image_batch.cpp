//
// Created by liangjie on 2024/5/9.
//

#include "cc/image_batch.h"

#include "cc/image.h"
#include "cc/handle.h"
#include "cc/renderer.h"
#include "cc/image_data.h"
#include "cc/zone.h"
#include "SDL2/SDL_image.h"

void ImageBatchHandleFinalizer(void * handle) {
    SDL_DestroyTexture(static_cast<SDL_Texture *>(handle));
}

CC::ImageBatch::ImageBatch() : Handle(nullptr), context(Make<Context>()) {}

CC::ImageBatch::ImageBatch(const CC::ImageBatch &image)
    : Handle(RetainHandle(image.Handle)), context(Retain(image.context)) {}

CC::ImageBatch::ImageBatch(CC::ImageBatch &&image)
    : Handle(image.Handle), context(image.context) {
    image.Handle = nullptr;
    image.context = nullptr;
}

CC::ImageBatch::~ImageBatch() {
    if (Handle == nullptr) return;

    Close();
}

bool CC::ImageBatch::Open(const char *fileName) {
    if (Handle != nullptr) return true;

    auto surface = IMG_Load(fileName);

    if (surface == nullptr) return false;

    Handle = SDL_CreateTextureFromSurface(static_cast<SDL_Renderer *>(CC::Renderer::GetCurrent()->Handle), surface);
    Handle = RetainHandle(Handle);

    SDL_FreeSurface(surface);

    return Handle != nullptr;
}

bool CC::ImageBatch::Open(const void * buffer, CC::Size size) {
    if (Handle != nullptr) return true;

    IMG_Animation * anime = IMG_LoadAnimation_RW(SDL_RWFromConstMem(buffer, size), 1);

    if (anime == nullptr) return false;

    Handle = SDL_CreateTextureFromSurface(
        static_cast<SDL_Renderer *>(CC::Renderer::GetCurrent()->Handle), anime->frames[0]);
    Handle = RetainHandle(Handle);
    context->animeHandle = RetainHandle(anime);
    context->Frame = 0;

    return Handle != nullptr;
}

bool CC::ImageBatch::Open(CC::ImageData * imageData) {
    if (Handle != nullptr) return true;

    Handle = SDL_CreateTextureFromSurface(
        static_cast<SDL_Renderer *>(CC::Renderer::GetCurrent()->Handle),
        static_cast<SDL_Surface *>(imageData->Handle));
    Handle = RetainHandle(Handle);

    return Handle != nullptr;
}

bool CC::ImageBatch::Open(CC::Renderer * renderer, const char *fileName) {
    if (Handle != nullptr) return true;

    auto surface = IMG_Load(fileName);

    if (surface == nullptr) return false;

    Handle = SDL_CreateTextureFromSurface(static_cast<SDL_Renderer *>(renderer->Handle), surface);
    Handle = RetainHandle(Handle);

    SDL_FreeSurface(surface);

    return Handle != nullptr;
}

bool CC::ImageBatch::Open(CC::Renderer * renderer, const void * buffer, CC::Size size) {
    if (Handle != nullptr) return true;

    IMG_Animation * anime = IMG_LoadAnimation_RW(SDL_RWFromConstMem(buffer, size), 1);

    if (anime == nullptr) return false;

    Handle = SDL_CreateTextureFromSurface(
        static_cast<SDL_Renderer *>(renderer->Handle), anime->frames[0]);
    Handle = RetainHandle(Handle);
    context->animeHandle = RetainHandle(anime);
    context->Frame = 0;

    return Handle != nullptr;
}

bool CC::ImageBatch::Open(CC::Renderer * renderer, CC::ImageData * imageData) {
    if (Handle != nullptr) return true;

    Handle = SDL_CreateTextureFromSurface(
        static_cast<SDL_Renderer *>(renderer->Handle),
        static_cast<SDL_Surface *>(imageData->Handle));
    Handle = RetainHandle(Handle);

    return Handle != nullptr;
}

void CC::ImageBatch::Close() {
    if (Handle == nullptr) return;

    ReleaseHandle(Handle, ImageBatchHandleFinalizer);

    Handle = nullptr;
}

void CC::ImageBatch::NextFrame() {
    if (context->animeHandle == nullptr) return;

    auto anime = static_cast<IMG_Animation *>(context->animeHandle);
    context->Frame++;

    if (context->Frame >= anime->count) context->Frame = 0;
}

void CC::ImageBatch::Render() {
    if (context->animeHandle == nullptr) return;

    auto anime = static_cast<IMG_Animation *>(context->animeHandle);
    auto renderer = static_cast<SDL_Renderer *>(CC::Renderer::GetCurrent()->Handle);

    auto texture = SDL_CreateTextureFromSurface(
        renderer,
        anime->frames[context->Frame]);

    // Backup
    auto target = SDL_GetRenderTarget(renderer);
    UInt8 rgba[4];
    SDL_GetRenderDrawColor(renderer, &rgba[0], &rgba[1], &rgba[2], &rgba[3]);

    SDL_SetRenderTarget(renderer, static_cast<SDL_Texture *>(Handle));
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_Rect ab = {0, 0, anime->w, anime->h};

    SDL_RenderCopy(renderer, texture, &ab, &ab);

    // Reset
    SDL_SetRenderDrawColor(renderer, rgba[0], rgba[1], rgba[2], rgba[3]);
    SDL_SetRenderTarget(renderer, target);
}

void *CC::ImageBatch::GetHandle() {
    return Handle;
}

CC::ImageBatch &CC::ImageBatch::operator=(const CC::ImageBatch &image) {
    if (this == &image) return *this;

    Close();
    Destroy(context);
    Handle = RetainHandle(image.Handle);
    context = Retain(image.context);

    return *this;
}

CC::ImageBatch &CC::ImageBatch::operator=(CC::ImageBatch &&image) {
    if (this == &image) return *this;

    Close();
    Destroy(context);
    Handle = image.Handle;
    context = image.context;
    image.Handle = nullptr;
    image.context = nullptr;

    return *this;
}
