//
// Created by liangjie on 2024/3/28.
//

#ifndef CHOCO_CPP_FLAGS_H
#define CHOCO_CPP_FLAGS_H

#include "cc/types.h"

namespace CC::Flags {
    struct Renderer {
        static const UInt32 Software;      /**< The renderer is a software fallback */
        static const UInt32 Hardware;      /**< The renderer uses hardware acceleration */
        static const UInt32 PresentVSYNC;  /**< Present is synchronized with the refresh rate */
        static const UInt32 TargetTexture; /**< The renderer supports endering to texture */
    };

    struct Window {
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
}

#endif //CHOCO_CPP_FLAGS_H
