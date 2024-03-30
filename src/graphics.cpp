//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/graphics.h"
#include "ui_context.h"
#include "SDL2/SDL.h"

void CC::Graphics::Draw(CC::Drawable &drawable,
                        CC::Int32 x, CC::Int32 y,
                        CC::Int32 radians,
                        CC::Int32 scaleX, CC::Int32 scaleY,
                        CC::Int32 offsetX, CC::Int32 offsetY) {
    auto renderer = UIContext::GetContext().windows.top()->renderer.get<SDL_Renderer>();
//    SDL_RenderCopy(renderer, drawable.)
}
