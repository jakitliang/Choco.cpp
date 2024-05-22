//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_WINDOW_H
#define CHOCO_CPP_WINDOW_H

#include "cc/flags.h"
#include "cc/ui_event.h"

namespace CC {
    struct Window {
        struct Context;

        void * Handle;

        Window();

        Window(const Window & window) = delete;

        Window(Window && window) noexcept;

        ~Window();

        bool Open(const char * title,
                  Int32 x, Int32 y,
                  Int32 width, Int32 height,
                  UInt32 flags, UInt32 modes = Flags::Renderer::Hardware);

        bool Open(void * windowHandle);

        void Close();

        UInt32 GetID();

        void onEvent(UIEvent & event);

        virtual void onStateChanged(UIWindowEvent & event);

        virtual void onKey(UIKeyboardEvent & event);

        virtual void onMouseMotion(UIMouseMotionEvent & event);

        virtual void onMouseButton(UIMouseButtonEvent & event);

        virtual void onMouseWheel(UIMouseWheelEvent & event);

        virtual void onOpen();

        virtual void onClose();

        virtual void Update(UInt64 deltaTime);

        virtual void Draw();

        Vector2 GetPosition();

        void SetPosition(const Vector2 & position);

        void SetRelativePosition(const Vector2 & position);

        void SetTransparent(Byte opacity);

        Window & operator=(const Window & window) = delete;

        Window & operator=(Window && window) noexcept;

        static Window * Current();
    };
}

#endif //CHOCO_CPP_WINDOW_H
