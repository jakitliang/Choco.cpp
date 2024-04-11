//
// Created by liangjie on 2024/4/3.
//

#ifndef CHOCO_CPP_RENDERER_CONTEXT_H
#define CHOCO_CPP_RENDERER_CONTEXT_H

#include "cc/renderer.h"
#include "cc/linked_list.h"
#include <unordered_map>
#include <stack>

struct CC::Renderer::Context {
    using RendererMapType = std::unordered_map<void *, void *>; // [Renderer] -> Window
    using WindowMapType = std::unordered_map<void *, CC::Renderer>; // [Window] -> Renderer

    RendererMapType RendererMap;
    WindowMapType WindowsMap;

    CC::Renderer * Open(void * windowHandle, Int32 index, UInt32 flags);

    void Close(void * handle);

    static Context & GetContext();
};

#endif //CHOCO_CPP_RENDERER_CONTEXT_H
