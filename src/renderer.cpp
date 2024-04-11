//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/window.h"
#include "cc/renderer.h"
#include "renderer_context.h"
#include "SDL2/SDL.h"
#include <vector>
#include <unordered_map>

static std::vector<SDL_FPoint> Points = {};
static std::vector<SDL_FRect> Rects = {};

CC::Renderer::Renderer() : Handle(nullptr) {}

CC::Renderer::Renderer(CC::Renderer &&renderer) noexcept
    : Handle(renderer.Handle) { renderer.Handle = nullptr; }

CC::Renderer::~Renderer() {
    Close();
}

CC::Renderer * CC::Renderer::Open(void * windowHandle, Int32 index, UInt32 flags) {
    return Context::GetContext().Open(windowHandle, index, flags);
}

void CC::Renderer::Close() {
    if (Handle == nullptr) return;

    Context::GetContext().Close(Handle);
    Handle = nullptr;
}

CC::Renderer &CC::Renderer::operator=(CC::Renderer &&renderer) noexcept {
    if (this == &renderer) return *this;

    Close();
    Handle = renderer.Handle;
    renderer.Handle = nullptr;

    return *this;
}

void CC::Renderer::DrawLine(Float32 startX, Float32 startY, Float32 endX, Float32 endY) {
    SDL_RenderDrawLineF(static_cast<SDL_Renderer *>(Handle), startX, startY, endX, endY);
}

void CC::Renderer::DrawLine(const CC::Vector2 &start, const CC::Vector2 &end) {
    DrawLine(start.X, start.Y, end.X, end.Y);
}

void CC::Renderer::DrawLines(const CC::Vector2 *lines, CC::UInt32 count) {
    Points.clear();

    for (int i = 0; i < count; ++i) {
        Points.emplace_back(SDL_FPoint{lines[i].X, lines[i].Y});
    }

    SDL_RenderDrawLinesF(static_cast<SDL_Renderer *>(Handle), &Points[0], (int) count);
}

void CC::Renderer::DrawPoint(CC::Float32 positionX, CC::Float32 positionY) {
    SDL_RenderDrawPointF(static_cast<SDL_Renderer *>(Handle), positionX, positionY);
}

void CC::Renderer::DrawPoint(const CC::Vector2 & position) {
    DrawPoint(position.X, position.Y);
}

void CC::Renderer::DrawPoints(const CC::Vector2 (*positions)[], CC::UInt32 count) {
    Points.clear();

    for (int i = 0; i < count; ++i) {
        Points.emplace_back(SDL_FPoint{(*positions)[i].X, (*positions)[i].Y});
    }

    SDL_RenderDrawLinesF(static_cast<SDL_Renderer *>(Handle), &Points[0], (int) count);
}

void CC::Renderer::DrawRect(CC::Float32 x, CC::Float32 y, CC::Float32 width, CC::Float32 height) {
    SDL_FRect rect{x, y, width, height};

    SDL_RenderDrawRectF(static_cast<SDL_Renderer *>(Handle), &rect);
}

void CC::Renderer::DrawRect(const CC::Rect &rect) {
    DrawRect(rect.X, rect.Y, rect.Width, rect.Height);
}

void CC::Renderer::DrawRects(const CC::Rect (*rects)[], CC::UInt32 count) {
    Rects.clear();

    for (int i = 0; i < count; ++i) {
        Rects.emplace_back(SDL_FRect{(*rects)[i].X, (*rects)[i].Y,
                                     (*rects)[i].Width, (*rects)[i].Height});
    }

    SDL_RenderDrawRectsF(static_cast<SDL_Renderer *>(Handle), &Rects[0], (int) count);
}

void CC::Renderer::Draw(void * textureHandle,
                        CC::Float32 x, CC::Float32 y,
                        CC::Float32 r,
                        CC::Float32 scaleX, CC::Float32 scaleY,
                        CC::Float32 originX, CC::Float32 originY) {
    Uint32 format;
    Int32 access, width, height;
    SDL_QueryTexture(static_cast<SDL_Texture *>(textureHandle), &format, &access, &width, &height);

    SDL_FRect dst{x, y, (Float32) width * scaleX, (Float32) height * scaleY};
    SDL_FPoint origin{originX + dst.w / 2,
                      originY + dst.h / 2};

    SDL_RenderCopyExF(static_cast<SDL_Renderer *>(Handle),
                      static_cast<SDL_Texture *>(textureHandle),
                      nullptr,
                      &dst,
                      r,
                      &origin,
                      SDL_FLIP_NONE);
}

void CC::Renderer::Draw(void * textureHandle,
                        CC::Rect quad,
                        CC::Float32 x, CC::Float32 y,
                        CC::Float32 r,
                        CC::Float32 scaleX, CC::Float32 scaleY,
                        CC::Float32 originX, CC::Float32 originY) {
    Uint32 format;
    int access, width, height;
    SDL_QueryTexture(static_cast<SDL_Texture *>(textureHandle), &format, &access, &width, &height);

    SDL_Rect src{static_cast<int>(quad.X), static_cast<int>(quad.Y),
                 static_cast<int>(quad.Width * scaleX), static_cast<int>(quad.Height * scaleY)};
    SDL_FRect dst{x, y, quad.Width * scaleX, quad.Height * scaleY};
    SDL_FPoint origin{originX + dst.w / 2,
                      originY + dst.h / 2};

    SDL_RenderCopyExF(static_cast<SDL_Renderer *>(Handle), static_cast<SDL_Texture *>(textureHandle), &src, &dst, r, &origin, SDL_FLIP_NONE);
}

void CC::Renderer::SetColor(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha) {
    SDL_SetRenderDrawColor(static_cast<SDL_Renderer *>(Handle), red, green, blue, alpha);
}

void CC::Renderer::Clear() {
    SDL_RenderClear(static_cast<SDL_Renderer *>(Handle));
}

void CC::Renderer::Present() {
    SDL_RenderPresent(static_cast<SDL_Renderer *>(Handle));
}

CC::Renderer * CC::Renderer::GetCurrent() {
    auto window = Window::Current();
    return window == nullptr ? nullptr : &Context::GetContext().WindowsMap[window->Handle];
}

CC::Renderer * CC::Renderer::GetWithWindow(CC::Window * window) {
    return window == nullptr ? nullptr : &Context::GetContext().WindowsMap[window->Handle];
}
