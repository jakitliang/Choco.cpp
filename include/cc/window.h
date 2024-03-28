//
// Created by liangjie on 2024/3/26.
//

#ifndef CHOCO_CPP_WINDOW_H
#define CHOCO_CPP_WINDOW_H

#include "cc/types.h"
#include "cc/variant.h"
#include "cc/renderer.h"

namespace CC {
    using Window = Var<WindowHandle>;

    template<>
    struct Var<WindowHandle> {
        struct Flags {
            static const UInt32 FullScreen;
            static const UInt32 OpenGL;
            static const UInt32 Shown;
            static const UInt32 Hidden;
            static const UInt32 Borderless;
            static const UInt32 Resizable;
            static const UInt32 Minimized;
            static const UInt32 Maximized;
            static const UInt32 MouseGrabbed;
            static const UInt32 InputFocus;
            static const UInt32 MouseFocus;
            static const UInt32 FullscreenDesktop;
            static const UInt32 Foreign;
            static const UInt32 AllowHDPI;
            static const UInt32 MouseCapture;
            static const UInt32 AlwaysOnTop;
            static const UInt32 SkipTaskBar;
            static const UInt32 Utility;
            static const UInt32 Tooltip;
            static const UInt32 PopupMenu;
            static const UInt32 KeyboardGrabbed;
            static const UInt32 Vulkan;
            static const UInt32 Metal;
            static const UInt32 InputGrabbed;
        };

        struct Delegate {
            virtual void nDraw(Window * wnd) = 0;

            virtual void onUpdate(Int64 dt) = 0;

            virtual void onMouseDown() = 0;
        };

        WindowHandle * handle;

        Renderer * renderer;

        Delegate * Delegate;

        Var();

        Var(const Var & var);

        Var(Var && var);

        ~Var();

        bool Open(const char * title,
                  Int32 x, Int32 y,
                  Int32 width, Int32 height,
                  UInt32 flags, UInt32 modes = Renderer::Flags::Hardware);

        void Close();

        void on(UInt32 event);
    };
}

#endif //CHOCO_CPP_WINDOW_H
