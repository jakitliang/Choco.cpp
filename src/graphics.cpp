//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/graphics.h"
#include "ui_context.h"
#include "SDL2/SDL.h"

CC::UIContext & GetContext() {
    return CC::UIContext::GetContext();
}

void CC::Graphics::Draw(CC::Drawable &drawable,
                        CC::Int32 x, CC::Int32 y,
                        CC::Int32 radians,
                        CC::Int32 scaleX, CC::Int32 scaleY,
                        CC::Int32 offsetX, CC::Int32 offsetY) {
    auto renderer = UIContext::GetContext().RendererState.top()<SDL_Renderer>();
//    SDL_RenderCopy(renderer, drawable.)
}
