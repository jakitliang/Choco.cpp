//
// Created by Jakit on 2024/3/30.
//

#ifndef CHOCO_CPP_UI_CONTEXT_H
#define CHOCO_CPP_UI_CONTEXT_H

#include "cc/window.h"
#include "cc/texture.h"
#include <unordered_map>

namespace CC {
    using WindowMap = unordered_map<UInt32, Window>;
    using TextureMap = unordered_map<UInt32, Texture>;

    struct UIContext {
        WindowMap Windows;
        TextureMap Textures;

        static UIContext & GetContext();
    };
}

#endif //CHOCO_CPP_UI_CONTEXT_H
