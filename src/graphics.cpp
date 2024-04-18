//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/graphics.h"
#include "cc/window.h"
#include "cc/renderer.h"
#include "cc/font.h"
#include "SDL2/SDL.h"

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
