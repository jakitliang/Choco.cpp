//
// Created by Jakit on 2024/3/30.
//

#ifndef CHOCO_CPP_UI_CONTEXT_H
#define CHOCO_CPP_UI_CONTEXT_H

#include "cc/window.h"
#include "cc/texture.h"
#include <unordered_map>
#include <stack>

namespace CC {
    using WindowMap = std::unordered_map<UInt32, Window>;
    using TextureMap = std::unordered_map<UInt32, Texture>;
    using RendererStack = std::stack<Renderer>;

    struct UIContext {
        WindowMap Windows;
        TextureMap Textures;
        RendererStack RendererState;

        static UIContext & GetContext();
    };
}

#endif //CHOCO_CPP_UI_CONTEXT_H
