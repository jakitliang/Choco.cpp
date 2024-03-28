//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#ifndef CHOCO_CPP_IO_H
#define CHOCO_CPP_IO_H

#include "types.h"

namespace CC {
    struct IO {
        virtual ~IO() = default;

        virtual Size Write(void * buffer, Size length) = 0;

        virtual Size WriteNonBlock(void * buffer, Size length) = 0;

        virtual Size Read(void * buffer, Size length) = 0;

        virtual Size ReadNonBlock(void * buffer, Size length) = 0;

        virtual bool Close() = 0;

        virtual bool IsClosed() = 0;
    };
}

#endif //CHOCO_CPP_IO_H
