//
// Created by liangjie on 2024/4/3.
//

#include "renderer_context.h"

static CC::Renderer::Context RendererContext = {};

CC::Renderer::Context & CC::Renderer::Context::GetContext() {
    return RendererContext;
}
