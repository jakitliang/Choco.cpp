//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#ifndef CHOCO_CPP_APPLICATION_H
#define CHOCO_CPP_APPLICATION_H

#include "cc/types.h"

namespace CC {
    struct Application {
        virtual ~Application();

        // CLI mode
        bool Open();

        void Close();

        bool Run();

        virtual void onOpen();

        virtual void onClose();

        virtual void onEvent(UInt32 event);
    };
}

#endif //CHOCO_CPP_APPLICATION_H
