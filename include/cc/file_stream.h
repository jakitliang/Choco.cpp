//
// Created by Jakit on 2024/3/11.
//

#ifndef CC_FILE_H
#define CC_FILE_H

#include "cc/object.h"
#include "cc/stream.h"

namespace CC {
    struct File : IStream {
        Size onWrite(const void * buffer, Size length);

        Size onRead(void * buffer, Size length);

        bool onClose();
    };
}

#endif //CC_FILE_H
