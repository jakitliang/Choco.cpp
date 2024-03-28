//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#ifndef CHOCO_CPP_APPLICATION_H
#define CHOCO_CPP_APPLICATION_H

#include "cc/graphics.h"
#include "cc/window.h"

namespace CC {
    struct Application {
        Window mainWindow;

        virtual ~Application();

        // CLI mode
        bool Open();

        // GUI mode
        bool Open(const char * title,
                  Int32 x, Int32 y,
                  Int32 width, Int32 height,
                  UInt32 flags, UInt32 modes = Flags::Renderer::Hardware);

        void Close();

        bool Run();

        static Application & Context();
    };
}

#endif //CHOCO_CPP_APPLICATION_H
