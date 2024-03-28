//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_WINDOW_H
#define CHOCO_CPP_WINDOW_H

#include "cc/flags.h"
#include "cc/renderer.h"
#include "cc/texture.h"
#include "cc/view.h"
#include "cc/linked_list.h"

namespace CC {
    struct Window : Handle, IView {
        struct Delegate {
            virtual void onMouseDown() = 0;
        };

        Renderer renderer;

        Texture texture;

        LinkedList<Window> subWindows;

        ~Window() override;

        bool Open(const char * title,
                  Int32 x, Int32 y,
                  Int32 width, Int32 height,
                  UInt32 flags, UInt32 modes = Flags::Renderer::Hardware);

        void Close();

        void on(UInt32 event);
    };
}

#endif //CHOCO_CPP_WINDOW_H
