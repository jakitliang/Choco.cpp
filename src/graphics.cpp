//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/graphics.h"
#include "cc/window.h"
#include "cc/renderer.h"
#include "cc/font.h"
#include "SDL2/SDL.h"
#include <vector>

void CC::Graphics::Draw(CC::Texture * drawable,
                        CC::Float32 x, CC::Float32 y,
                        CC::Float32 r,
                        CC::Float32 scaleX, CC::Float32 scaleY,
                        CC::Float32 originX, CC::Float32 originY) {
    Renderer::GetCurrent()->Draw(drawable->GetHandle(),
                                 x, y, r,
                                 scaleX, scaleY,
                                 originX, originY);
}

void CC::Graphics::Line(CC::Float32 startX, CC::Float32 startY, CC::Float32 endX, CC::Float32 endY) {
    Renderer::GetCurrent()->DrawLine(startX, startY, endX, endY);
}

void CC::Graphics::Line(const CC::Vector2 &start, const CC::Vector2 &end) {
    Renderer::GetCurrent()->DrawLine(start, end);
}

void CC::Graphics::Line(const CC::Vector2 *lines, CC::UInt32 count) {
    Renderer::GetCurrent()->DrawLines(lines, count);
}

void CC::Graphics::Rectangle(Float32 x, Float32 y, Float32 width, Float32 height, bool filled) {
    Renderer::GetCurrent()->DrawRect(x, y, width, height, filled);
}

void CC::Graphics::Rectangle(const CC::Rect & rect, bool filled) {
    Renderer::GetCurrent()->DrawRect(rect, filled);
}

void CC::Graphics::Rectangles(const CC::Rect (*rects)[], UInt32 count, bool filled) {
    Renderer::GetCurrent()->DrawRects(rects, count, filled);
}

void CC::Graphics::Circle(CC::Float32 offsetX, CC::Float32 offsetY, CC::Float32 radius, int density) {
    float angle = 360.0f / density;

    int triangleCount = density - 2;

    std::vector<CC::Vertex> temp;
    std::vector<CC::Vertex> circle;
    CC::Color color = Renderer::GetCurrent()->GetColor();

    // positions
    for (int i = 0; i < density; i++) {
        float currentAngle = angle * i;
        float x = radius * cos((currentAngle * M_PI) / 180);
        float y = radius * sin((currentAngle * M_PI) / 180);
        float z = 0.0f;

        temp.push_back({{x + offsetX, y + offsetY, z}, color, {0, 0}});
    }

    // push indexes of each triangle points
    for (int i = 0; i < triangleCount; i++) {
        circle.push_back(temp[0]);
        circle.push_back(temp[i + 1]);
        circle.push_back(temp[i + 2]);
    }

    Geometry(nullptr, &circle[0], circle.size(), nullptr, 0);
}

void CC::Graphics::Geometry2D(CC::Texture *drawable,
                              const CC::Vertex *vertexes, CC::UInt32 count,
                              const CC::UInt32 *indices, CC::UInt32 indicesCount) {
    Renderer::GetCurrent()->DrawGeometry2D(drawable,
                                           vertexes, count,
                                           indices, indicesCount);
}

void CC::Graphics::Geometry(CC::Texture *drawable,
                            const CC::Vertex *vertexes, CC::UInt32 count,
                            const CC::UInt32 *indices, CC::UInt32 indicesCount) {
    Renderer::GetCurrent()->DrawGeometry3D(drawable,
                                           vertexes, count,
                                           indices, indicesCount);
}

bool CC::Graphics::IsInRect(const CC::Vector2 & point, const CC::Rect & rect) {
    SDL_FPoint p{point.X, point.Y};
    SDL_FRect r{rect.X, rect.Y, rect.Width, rect.Height};
    return SDL_PointInFRect(&p, &r) == SDL_TRUE;
}

void CC::Graphics::Print(const char * text,
                         CC::Font * font,
                         CC::Float32 x, CC::Float32 y,
                         CC::Float32 r,
                         CC::Float32 scaleX, CC::Float32 scaleY,
                         CC::Float32 originX, CC::Float32 originY) {
    Renderer::GetCurrent()->DrawText(text, font, x, y, r,
                                     scaleX, scaleY, originX, originY);
}

void CC::Graphics::SetColor(CC::UInt8 red, CC::UInt8 green, CC::UInt8 blue, CC::UInt8 alpha) {
    Renderer::GetCurrent()->SetColor(red, green, blue, alpha);
}

void CC::Graphics::Clear() {
    auto renderer = Renderer::GetCurrent();
    renderer->SetColor(0, 0, 0, 0);
    renderer->Clear();
}

void CC::Graphics::Present() {
    Renderer::GetCurrent()->Present();
}
