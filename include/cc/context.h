//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#ifndef CHOCO_CPP_CONTEXT_H
#define CHOCO_CPP_CONTEXT_H

#include "cc/handle.h"

namespace CC {
    struct Context {
        void * handle;
        Handle::Finalizer finalizer;

        Context();

        Context(const Context & context);

        Context & operator=(Context & context);

        Context(void * handle, Handle::Finalizer finalizer);
    };
}

#endif //CHOCO_CPP_CONTEXT_H
