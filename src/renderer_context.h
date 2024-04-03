//
// Created by liangjie on 2024/4/3.
//

#ifndef CHOCO_CPP_RENDERER_CONTEXT_H
#define CHOCO_CPP_RENDERER_CONTEXT_H

#include "cc/renderer.h"
#include <unordered_map>
#include <stack>

struct CC::Renderer::Context {
    using RendererMapType = std::unordered_map<UInt32, CC::Renderer>;
    using RendererStackType = std::stack<CC::Renderer *>;

    RendererMapType Renderers;
    RendererStackType State;

    static Context & GetContext();
};

#endif //CHOCO_CPP_RENDERER_CONTEXT_H
