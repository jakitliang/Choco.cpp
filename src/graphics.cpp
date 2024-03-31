//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#include "cc/graphics.h"
#include "ui_context.h"
#include "SDL2/SDL.h"

CC::UInt32 CC::Graphics::CreateWindow(const char *title,
                                      Int32 x, Int32 y,
                                      Int32 width, Int32 height,
                                      UInt32 flags, UInt32 modes = Flags::Renderer::Hardware) {
    Window window;

    if (!window.Open(title, x, y, width, height, flags, modes)) {
        return 0;
    }

    UIContext::GetContext().Windows[window.GetID()] = window;
}

CC::Window * CC::Graphics::GetWindow(CC::UInt32 windowID) {
    auto ret = UIContext::GetContext().Windows.find(windowID);
    if (ret->)
}

void CC::Graphics::Draw(CC::Drawable &drawable,
                        CC::Int32 x, CC::Int32 y,
                        CC::Int32 radians,
                        CC::Int32 scaleX, CC::Int32 scaleY,
                        CC::Int32 offsetX, CC::Int32 offsetY) {
    auto renderer = UIContext::GetContext().windows.top()->renderer.get<SDL_Renderer>();
//    SDL_RenderCopy(renderer, drawable.)
}
