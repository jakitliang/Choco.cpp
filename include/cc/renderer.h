//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_RENDERER_H
#define CHOCO_CPP_RENDERER_H

#include "cc/handle.h"

namespace CC {
    struct Renderer : Handle {
        ~Renderer() override;

        bool Open(Handle * windowHandle, Int32 index, UInt32 flags);

        void Close();
    };
}

#endif //CHOCO_CPP_RENDERER_H
