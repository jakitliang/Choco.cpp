//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_WINDOW_H
#define CHOCO_CPP_WINDOW_H

#include "cc/flags.h"

namespace CC {
    struct Window {
        struct Context;

        struct Delegate {
            virtual void onMouseDown() = 0;
        };

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

        void on(UInt32 event);

        virtual void Update(UInt64 deltaTime);

        virtual void Draw();

        Window & operator=(const Window & window) = delete;

        Window & operator=(Window && window) noexcept;

        static Window * Current();
    };
}

#endif //CHOCO_CPP_WINDOW_H
