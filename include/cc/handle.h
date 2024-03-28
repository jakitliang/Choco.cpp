//
// Created by liangjie on 2024/3/27.
//

#ifndef CHOCO_CPP_HANDLE_H
#define CHOCO_CPP_HANDLE_H

#include "cc/types.h"

namespace CC {
    struct Handle {
        using Type = void *;

        Type * object;

        Handle();

        Handle(const Handle & handle);

        Handle(Handle && handle);

        virtual ~Handle();

        template<typename T>
        T * & get() {
            using CastType = T *;
            return *reinterpret_cast<CastType *>(object);
        }
    };
}

#endif //CHOCO_CPP_HANDLE_H
