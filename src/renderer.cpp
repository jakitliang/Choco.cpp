//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/renderer.h"
#include "cc/window.h"
#include "SDL2/SDL.h"

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

    SDL_RenderDrawLine(renderer, startX, startY, endX, endY);
}

void CC::Renderer::DrawLine(const CC::Vector2 &start, const CC::Vector2 &end) {
    DrawLine(start.X, start.Y, end.X, end.Y);
}

void CC::Renderer::DrawLines(const CC::Vector2 (*lines)[], CC::UInt32 count) {
    SDL_Point points[count];
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    for (int i = 0; i < count; ++i) {
        points[i].x = (*lines)[i].X;
        points[i].y = (*lines)[i].Y;
    }

    SDL_RenderDrawLines(renderer, &points[0], count);
}

void CC::Renderer::DrawPoint(CC::Float32 positionX, CC::Float32 positionY) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    SDL_RenderDrawPoint(renderer, positionX, positionY);
}

void CC::Renderer::DrawPoint(const CC::Vector2 & position) {
    DrawPoint(position.X, position.Y);
}

void CC::Renderer::DrawPoints(const CC::Vector2 (*positions)[], CC::UInt32 count) {
    SDL_Point points[count];
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    for (int i = 0; i < count; ++i) {
        points[i].x = (*positions)[i].X;
        points[i].y = (*positions)[i].Y;
    }

    SDL_RenderDrawLines(renderer, &points[0], count);
}

void CC::Renderer::DrawRect(CC::Float32 x, CC::Float32 y, CC::Float32 width, CC::Float32 height) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    SDL_Rect rect{static_cast<int>(x),
                  static_cast<int>(y),
                  static_cast<int>(width),
                  static_cast<int>(height)};

    SDL_RenderDrawRect(renderer, &rect);
}

void CC::Renderer::DrawRect(const CC::Rect &r) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    SDL_Rect rect{static_cast<int>(r.X),
                  static_cast<int>(r.Y),
                  static_cast<int>(r.Width),
                  static_cast<int>(r.Height)};

    SDL_RenderDrawRect(renderer, &rect);
}

void CC::Renderer::DrawRects(const CC::Rect (*rects)[], CC::UInt32 count) {
    SDL_Rect sdlRects[count];
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    for (int i = 0; i < count; ++i) {
        sdlRects[i].x = (*rects)[i].X;
        sdlRects[i].y = (*rects)[i].Y;
        sdlRects[i].w = (*rects)[i].Width;
        sdlRects[i].h = (*rects)[i].Height;
    }

    SDL_RenderDrawRects(renderer, &sdlRects[0], count);
}

void CC::Renderer::Draw(CC::Texture *texture) {
    auto & renderer = get<SDL_Renderer>();
    if (renderer == nullptr) return;

    SDL_RenderCopy(renderer, texture->get<SDL_Texture>(), )
}
