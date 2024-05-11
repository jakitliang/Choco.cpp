//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#include "cc/application.h"
#include "cc/window.h"
#include "window_context.h"
#include "cc/ui_event.h"
#include "cc/graphics.h"
#include "cc/dispatch_queue.h"
//#include "ui_context.h"
//#include "window_context.h"
#include "SDL2/SDL.h"
#include <unordered_map>
#include <queue>

const CC::UIEvent EmptyEvent = {CC::UIEventType::FirstEvent};
static CC::Application * CurrentApplication = nullptr;

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

CC::Application::~Application() {}

bool CC::Application::Open() {
    if (CurrentApplication) return true;

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0) {
        CurrentApplication = this;
        onOpen();
        return true;
    }

    return false;
}

void CC::Application::Close() {
    if (CurrentApplication == nullptr) return;
    SDL_Quit();
    CurrentApplication = nullptr;
}

void ProcessEvent(const SDL_Event & event) {
    auto uiEvent = CC::UIEvent{event.type};
    auto uiEventType = uiEvent.Type;

    if (uiEventType == SDL_WINDOWEVENT) {
        // Window 200+
        uiEvent.window = {event.window.timestamp,
                          event.window.windowID,
                          event.window.event};
        CC::WindowEvents::Enqueue(event.window.windowID, uiEvent);

    } else if (uiEventType < SDL_MOUSEMOTION) {
        // Keyboard 300+
        if (uiEventType == SDL_KEYDOWN || uiEventType == SDL_KEYUP) {
            uiEvent.key = {event.key.timestamp,
                           event.key.windowID,
                           event.key.state,
                           event.key.repeat};
            CC::WindowEvents::Enqueue(event.key.windowID, uiEvent);
        }

    } else if (uiEventType < SDL_JOYAXISMOTION) {
        // Mouse
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

void ApplicationUpdate(CC::UInt64 timeDiff) {
    for (auto & wnd : CC::Window::Context::GetContext()) {
        auto wndID = wnd->GetID();
        while (CC::WindowEvents::Poll(wndID)) {
            auto event = CC::WindowEvents::Dequeue(wndID);
            wnd->onEvent(event);
        }

        wnd->Update(timeDiff);
    }
}

void ApplicationDraw() {
    for (auto & wnd : CC::Window::Context::GetContext()) {
        CC::Graphics::Clear();
        wnd->Draw();
        CC::Graphics::Present();
    }
}

bool CC::Application::Run() {
    UInt64 tick = SDL_GetTicks64();
    UInt64 tickStep = 10;
    UInt64 timeOut = tick + tickStep;
    UInt64 tickDiff = 0;
    UInt64 tickSecond = tick + 1000;

    while (CurrentApplication) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            // Quit event
            if (event.type == SDL_QUIT) {
                CurrentApplication = nullptr;
                onClose();
                return true;
            }

            // Application event
            if (event.type > SDL_QUIT && event.type <= SDL_APP_DIDENTERFOREGROUND) {
                onEvent(event.type);
                continue;
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
        ApplicationUpdate(tickDiff);

        DispatchQueue::Process();

        // On draw
        ApplicationDraw();

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

void CC::Application::onOpen() {}

void CC::Application::onClose() {}

void CC::Application::onEvent(CC::UInt32 event) {}
