//
// Created by Jakit on 2024/3/30.
//

#ifndef CHOCO_CPP_UI_CONTEXT_H
#define CHOCO_CPP_UI_CONTEXT_H

#include "cc/window.h"
#include "cc/texture.h"
#include "cc/ui_event.h"
#include <unordered_map>
#include <stack>
#include <queue>

namespace CC {
    using WindowMap = std::unordered_map<UInt32, Window>;
    using TextureMap = std::unordered_map<UInt32, Texture>;
    using RendererStack = std::stack<Renderer>;
    using EventMap = std::unordered_map<CC::UInt32, std::queue<CC::UIEvent>>;

    struct UIContext {
        struct WindowEvents;

        WindowMap Windows;
        TextureMap Textures;
        RendererStack RendererState;

        static UIContext & GetContext();
    };

    struct UIContext::WindowEvents {
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

            if (windowEvents == events.end()) return {0};

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

#endif //CHOCO_CPP_UI_CONTEXT_H
