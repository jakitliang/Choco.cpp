//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/graphics.h"
#include "cc/window.h"
#include "cc/renderer.h"
#include "SDL2/SDL.h"

void CC::Graphics::Draw(Image * drawable,
                        CC::Int32 x, CC::Int32 y,
                        CC::Int32 radians,
                        CC::Int32 scaleX, CC::Int32 scaleY,
                        CC::Int32 offsetX, CC::Int32 offsetY) {
//    auto & renderer = UIContext::GetContext().RendererState.top();
//    renderer.Draw()
//    Renderer::GetCurrent()->Draw()
}

void CC::Graphics::Line(CC::Float32 startX, CC::Float32 startY, CC::Float32 endX, CC::Float32 endY) {
    Renderer::GetCurrent()->DrawLine(startX, startY, endX, endY);
}

void CC::Graphics::Line(const CC::Vector2 &start, const CC::Vector2 &end) {
    Renderer::GetCurrent()->DrawLine(start, end);
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