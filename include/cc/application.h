//
// Created by liangjie on 2024/3/27.
//

#ifndef CHOCO_CPP_APPLICATION_H
#define CHOCO_CPP_APPLICATION_H

#include "graphics.h"

namespace CC {
    struct Application {
        Application();

        ~Application();

        bool Run();

        static Application & Context();
    };
}

#endif //CHOCO_CPP_APPLICATION_H
