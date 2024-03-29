//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#include "cc/application.h"
#include "cc/linked_list.h"
#include "cc/ui_event.h"
#include "SDL2/SDL.h"
#include "cc/window.h"
#include <unordered_map>
#include <queue>

const CC::UIEvent EmptyEvent = {CC::UIEventType::FirstEvent};

namespace CC {
    using EventMap = std::unordered_map<CC::UInt32, std::queue<CC::UIEvent>>;

    struct WindowEvents {
        static void Enqueue(UInt32 windowID, const UIEvent & event) {
            auto windowEvents = events.find(windowID);

            if (windowEvents == WindowEvents::events.end()) {
                events[windowID] = {};
                windowEvents = events.find(windowID);
            }

            windowEvents->second.push(event);
        }

        static UIEvent Dequeue(UInt32 windowID) {
            auto windowEvents = events.find(windowID);

            if (windowEvents == events.end()) return EmptyEvent;

            auto event = windowEvents->second.front();
            windowEvents->second.pop();

            return event;
        }

        static bool Poll(UInt32 windowID) {
            auto windowEvents = events.find(windowID);

            if (windowEvents == events.end()) return false;

            if (windowEvents->second.empty()) return false;

            return true;
        }

        static EventMap events;
    };
}

static int ApplicationStatus = 0;

CC::EventMap CC::WindowEvents::events = {};

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

void ProcessEvent(const SDL_Event & event) {
    auto uiEvent = CC::UIEvent{event.type};
    auto uiEventType = uiEvent.Type;

    if (uiEventType >= SDL_KEYDOWN && uiEventType < SDL_MOUSEMOTION) {
        if (uiEventType == SDL_KEYDOWN || uiEventType == SDL_KEYUP) {
            uiEvent.key = {event.key.timestamp,
                           event.key.windowID,
                           event.key.state,
                           event.key.repeat};
            CC::WindowEvents::Enqueue(event.key.windowID, uiEvent);
        }

    } else if (uiEventType >= SDL_MOUSEMOTION && uiEventType < SDL_JOYAXISMOTION) {
        if (uiEventType == SDL_MOUSEMOTION) {
            uiEvent.motion = {event.motion.timestamp,
                              event.motion.windowID,
                              event.motion.which,
                              event.motion.state,
                              event.motion.x,
                              event.motion.y,
                              event.motion.xrel,
                              event.motion.yrel};
            CC::WindowEvents::Enqueue(event.motion.windowID, uiEvent);

        } else if (uiEventType == SDL_MOUSEBUTTONUP || uiEventType == SDL_MOUSEBUTTONDOWN) {
            uiEvent.button = {event.button.timestamp,
                              event.button.windowID,
                              event.button.which,
                              event.button.button,
                              event.button.state,
                              event.button.clicks,
                              event.button.x,
                              event.button.y};
            CC::WindowEvents::Enqueue(event.button.windowID, uiEvent);

        } else if (uiEventType == SDL_MOUSEWHEEL) {
            uiEvent.wheel = {event.wheel.timestamp,
                             event.wheel.windowID,
                             event.wheel.which,
                             event.wheel.x,
                             event.wheel.y,
                             event.wheel.direction,
                             event.wheel.preciseX,
                             event.wheel.preciseY,
                             event.wheel.mouseX,
                             event.wheel.mouseY};
            CC::WindowEvents::Enqueue(event.wheel.windowID, uiEvent);
        }
    }
}

void ApplicationUpdate(CC::Window & wnd, CC::UInt64 timeDiff) {
    wnd.Update(timeDiff);

    if (wnd.subWindows.Count()) {
        for (auto & w : wnd.subWindows) {
            w.Update(timeDiff);
        }
    }
}

void ApplicationDraw(CC::Window & wnd) {
    wnd.Draw();

    if (wnd.subWindows.Count()) {
        for (auto & w : wnd.subWindows) {
            w.Draw();
        }
    }
}

bool CC::Application::Run() {
    UInt64 tick = SDL_GetTicks64();
    UInt64 tickStep = 10;
    UInt64 timeOut = tick + tickStep;
    UInt64 tickDiff = 0;
    UInt64 tickSecond = tick + 1000;

    while (ApplicationStatus) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                ApplicationStatus = 0;
                return true;
            }

            // Application event
            if (event.type > SDL_QUIT && event.type <= SDL_APP_DIDENTERFOREGROUND) {
                OnEvent(event.type);
            }

            ProcessEvent(event);
        }

        tick = SDL_GetTicks64();
        tickDiff = timeOut - tick;

        if (tickDiff < 15) {
            SDL_Delay(5);
            continue;
        }

        timeOut = tick + tickStep;

        // On update
        ApplicationUpdate(mainWindow, tickDiff);

        // On draw
        ApplicationDraw(mainWindow);

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

void CC::Application::OnEvent(CC::UInt32 event) {}
