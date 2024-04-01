//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/renderer.h"
#include "cc/window.h"
#include "SDL2/SDL.h"
#include <vector>

static std::vector<SDL_FPoint> Points = {};
static std::vector<SDL_FRect> Rects = {};

CC::Renderer::~Renderer() {
    Close();
}

bool CC::Renderer::Open(Handle * windowHandle, Int32 index, UInt32 flags) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer) return true;

    renderer = SDL_CreateRenderer(windowHandle->get<SDL_Window>(), index, flags);

    return renderer != nullptr;
}

void CC::Renderer::Close() {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    SDL_DestroyRenderer(renderer);

    renderer = nullptr;
}

void CC::Renderer::DrawLine(Float32 startX, Float32 startY, Float32 endX, Float32 endY) {
    auto & renderer = get<SDL_Renderer>();

    if (renderer == nullptr) return;

    SDL_RenderDrawLineF(renderer, startX, startY, endX, endY);
}

void CC::Renderer::DrawLine(const CC::Vector2 &start, const CC::Vector2 &end) {
    DrawLine(start.X, start.Y, end.X, end.Y);
}

void CC::Renderer::DrawLines(const CC::Vector2 (*lines)[], CC::UInt32 count) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    Points.clear();

    for (int i = 0; i < count; ++i) {
        Points.emplace_back(SDL_FPoint{(*lines)[i].X, (*lines)[i].Y});
    }

    SDL_RenderDrawLinesF(renderer, &Points[0], (int) count);
}

void CC::Renderer::DrawPoint(CC::Float32 positionX, CC::Float32 positionY) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    SDL_RenderDrawPointF(renderer, positionX, positionY);
}

void CC::Renderer::DrawPoint(const CC::Vector2 & position) {
    DrawPoint(position.X, position.Y);
}

void CC::Renderer::DrawPoints(const CC::Vector2 (*positions)[], CC::UInt32 count) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    Points.clear();

    for (int i = 0; i < count; ++i) {
        Points.emplace_back(SDL_FPoint{(*positions)[i].X, (*positions)[i].Y});
    }

    SDL_RenderDrawLinesF(renderer, &Points[0], (int) count);
}

void CC::Renderer::DrawRect(CC::Float32 x, CC::Float32 y, CC::Float32 width, CC::Float32 height) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    SDL_FRect rect{x, y, width, height};

    SDL_RenderDrawRectF(renderer, &rect);
}

void CC::Renderer::DrawRect(const CC::Rect &rect) {
    DrawRect(rect.X, rect.Y, rect.Width, rect.Height);
}

void CC::Renderer::DrawRects(const CC::Rect (*rects)[], CC::UInt32 count) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    Rects.clear();

    for (int i = 0; i < count; ++i) {
        Rects.emplace_back(SDL_FRect{(*rects)[i].X, (*rects)[i].Y,
                                     (*rects)[i].Width, (*rects)[i].Height});
    }

    SDL_RenderDrawRectsF(renderer, &Rects[0], (int) count);
}

void CC::Renderer::Draw(CC::Handle * textureHandle,
                        CC::Float32 x, CC::Float32 y,
                        CC::Float32 r,
                        CC::Float32 scaleX, CC::Float32 scaleY,
                        CC::Float32 originX, CC::Float32 originY) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    Uint32 format;
    Int32 access, width, height;
    auto texture = textureHandle->get<SDL_Texture>();
    SDL_QueryTexture(texture, &format, &access, &width, &height);

    SDL_FRect dst{x, y, (Float32) width * scaleX, (Float32) height * scaleY};
    SDL_FPoint origin{originX + dst.w / 2,
                      originY + dst.h / 2};

    SDL_RenderCopyExF(renderer, texture, nullptr, &dst, r, &origin, SDL_FLIP_NONE);
}

void CC::Renderer::Draw(CC::Handle *textureHandle,
                        CC::Rect quad,
                        CC::Float32 x, CC::Float32 y,
                        CC::Float32 r,
                        CC::Float32 scaleX, CC::Float32 scaleY,
                        CC::Float32 originX, CC::Float32 originY) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    Uint32 format;
    int access, width, height;
    auto texture = textureHandle->get<SDL_Texture>();
    SDL_QueryTexture(texture, &format, &access, &width, &height);

    SDL_Rect src{static_cast<int>(quad.X), static_cast<int>(quad.Y),
                 static_cast<int>(quad.Width * scaleX), static_cast<int>(quad.Height * scaleY)};
    SDL_FRect dst{x, y, quad.Width * scaleX, quad.Height * scaleY};
    SDL_FPoint origin{originX + dst.w / 2,
                      originY + dst.h / 2};

    SDL_RenderCopyExF(renderer, texture, &src, &dst, r, &origin, SDL_FLIP_NONE);
}

void CC::Renderer::Clear() {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    SDL_RenderClear(renderer);
}
