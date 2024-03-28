//
// Created by Jakit on 2024/3/29.
//

#include "SDL2/SDL.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    auto window = SDL_CreateWindow(
            "WEBASM",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            500, 500,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_Event event;
    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}