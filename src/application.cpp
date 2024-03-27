//
// Created by liangjie on 2024/3/27.
//

#include "cc/application.h"
#include "cc/linked_list.h"
#include "SDL2/SDL.h"

//CC::LinkedList<Window>

static bool ApplicationStatus = false;

CC::Application::Application() {
    ApplicationStatus = true;
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
}

CC::Application::~Application() {
    ApplicationStatus = false;
    SDL_Quit();
}

bool CC::Application::Run() {
    while (ApplicationStatus) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                event.window.windowID
                ApplicationStatus = false;
            }
        }

        // On update

        // On draw
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,ourPNG,NULL,NULL);

        // Finally show what we've drawn
        SDL_RenderPresent(renderer);
    }
}
