//
// Created by Jakit on 2024/3/29.
//

#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace std;

struct Context {
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    SDL_Surface * surface;
};

bool main_loop(SDL_Renderer* renderer) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif
        return false;
    }
    SDL_RenderClear(renderer);

    cout << "what" << endl;

//    auto font = TTF_OpenFont("微软雅黑", 32);
//    auto fontSurface = TTF_RenderText_Solid(font, "Choco GUI", {255, 0, 0});
//    SDL_Rect fontRect{100, 100, 0, 0};
//    SDL_BlitSurface(fontSurface, NULL, context->surface, &fontRect);
//    SDL_FreeSurface(fontSurface);
//    TTF_CloseFont(font);

    SDL_RenderPresent(renderer);
    return true;
}

void run_main_loop(void * renderer) {
    main_loop((SDL_Renderer *) renderer);
}

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
            "Getting Started",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            800, 600,
            SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 255);

//    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);
//
//    auto context = new Context{window, renderer, texture, SDL_GetWindowSurface(window)};

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(run_main_loop, (void *) renderer, 0, true);
#else
//    while(main_loop(renderer)) {
//        SDL_Delay(0);
//    };
#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
