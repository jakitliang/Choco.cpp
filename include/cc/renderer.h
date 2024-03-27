//
// Created by liangjie on 2024/3/26.
//

#ifndef CHOCO_CPP_RENDERER_H
#define CHOCO_CPP_RENDERER_H

#include "cc/variant.h"
#include "cc/handle.h"
#include "cc/types.h"

namespace CC {
    using Renderer = Var<RendererHandle>;

    template<>
    struct Var<RendererHandle> {
        struct Flags {
            static const UInt32 Software;      /**< The renderer is a software fallback */
            static const UInt32 Hardware;      /**< The renderer uses hardware acceleration */
            static const UInt32 PresentVSYNC;  /**< Present is synchronized with the refresh rate */
            static const UInt32 TargetTexture; /**< The renderer supports endering to texture */
        };

        RendererHandle * handle;

        Var();

        Var(const Var & var);

        Var(Var && var);

        ~Var();

        bool Open(WindowHandle * windowHandle, Int32 index, UInt32 flags);

        void Close();
    };
}

#endif //CHOCO_CPP_RENDERER_H
