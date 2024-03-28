//
// Created by liangjie on 2024/3/27.
//

#include "cc/application.h"
#include "cc/linked_list.h"
#include "SDL2/SDL.h"
#include "cc/window.h"

static int ApplicationStatus = 0;

CC::Application::~Application() {
    Close();
}

bool CC::Application::Open() {
    if (!ApplicationStatus) {
        ApplicationStatus = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0 ? 1 : 0;
    }

    return ApplicationStatus;
}

bool CC::Application::Open(const char *title,
                      CC::Int32 x, CC::Int32 y,
                      CC::Int32 width, CC::Int32 height,
                      CC::UInt32 flags, CC::UInt32 modes) {
    if (!Open()) {
        return false;

    } else if (ApplicationStatus == 2) {
        return true;
    }

    if (mainWindow.Open(title, x, y, width, height, flags, modes)) ApplicationStatus = 2;

    return ApplicationStatus == 2;
}

void CC::Application::Close() {
    ApplicationStatus = 0;

    mainWindow.Close();

    SDL_Quit();
}

bool CC::Application::Run() {
    while (ApplicationStatus) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                ApplicationStatus = 0;
                return true;
            }
        }

        // On update

        // On draw
        // Gives us a clear "canvas"
//        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
//        SDL_RenderClear(renderer);
//
//        SDL_RenderCopy(renderer,ourPNG,NULL,NULL);

        // Finally show what we've drawn
//        SDL_RenderPresent(renderer);
    }

    return true;
}
