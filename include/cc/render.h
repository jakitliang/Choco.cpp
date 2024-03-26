//
// Created by liangjie on 2024/3/26.
//

#ifndef CHOCO_CPP_RENDER_H
#define CHOCO_CPP_RENDER_H

#include "cc/window.h"

namespace CC {
    struct RenderHandle {
        void * render;
    };

    template<>
    struct Var<RenderHandle> {
        struct Flags {
            static const UInt32 Software;      /**< The renderer is a software fallback */
            static const UInt32 Hardware;      /**< The renderer uses hardware acceleration */
            static const UInt32 PresentVSYNC;  /**< Present is synchronized with the refresh rate */
            static const UInt32 TargetTexture; /**< The renderer supports endering to texture */
        };

        RenderHandle * handle;

        Var();

        Var(const Var & var);

        Var(Var && var);

        ~Var();

        bool Open(Window * wnd, Int32 index, UInt32 flags);

        void Close();
    };

    using Render = Var<RenderHandle>;
}

#endif //CHOCO_CPP_RENDER_H
