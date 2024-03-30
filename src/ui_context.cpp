//
// Created by Jakit on 2024/3/30.
//

#include "ui_context.h"

static CC::UIContext context = {};

CC::UIContext & CC::UIContext::GetContext() {
    return context;
}
