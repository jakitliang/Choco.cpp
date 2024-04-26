//
// Created by liangjie on 2024/4/1.
//

#include "cc/rect.h"
#include "SDL2/SDL.h"

CC::Rect::Rect() : X(0), Y(0), Width(0), Height(0) {}

CC::Rect::Rect(CC::Float32 x, CC::Float32 y, CC::Float32 width, CC::Float32 height)
    : X(x), Y(y), Width(width), Height(height) {}

CC::Rect::Rect(CC::Float32 (&array)[4])
    : X(array[0]), Y(array[1]), Width(array[2]), Height(array[3]) {}

bool CC::Rect::Includes(const CC::Vector2 & position) const {
    SDL_FPoint sdlFPoint{position.X, position.Y};
    SDL_FRect sdlFRect{X, Y, Width, Height};

    return SDL_PointInFRect(&sdlFPoint, &sdlFRect) == SDL_TRUE;
}

bool CC::Rect::Includes(const CC::Rect &rect) const {
    SDL_FRect sdlFRect1{X, Y, Width, Height};
    SDL_FRect sdlFRect2{rect.X, rect.Y, rect.Width, rect.Height};

    return SDL_HasIntersectionF(&sdlFRect1, &sdlFRect2) == SDL_TRUE;
}
