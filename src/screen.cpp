//
// Created by Jakit on 2024/3/28.
//

#include "cc/screen.h"
#include "SDL2/SDL.h"

CC::Screen::Screen() {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    width = mode.w;
    height = mode.h;
}

CC::Screen::Screen(CC::Int32 index) {
    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(index, &mode);
    width = mode.w;
    height = mode.h;
}
