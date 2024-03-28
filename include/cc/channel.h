//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#ifndef CHOCO_CPP_CHANNEL_H
#define CHOCO_CPP_CHANNEL_H

#include "types.h"
#include "cc/data.h"
#include "cc/io.h"

namespace CC {
    struct Channel {
        struct Delegate {
            virtual Size onWrite() = 0;

            virtual Size onRead() = 0;

            virtual Size onClose() = 0;
        };

        Data * input;
        Data * output;
        IO * io;

        Channel();

        Channel(const Channel & channel);

        Channel(Channel && channel);

        Channel(IO * io);

        virtual ~Channel();

        virtual Size Write(const void * buffer, Size length);

        virtual Size WriteAsync(const void * buffer, Size length);

        virtual Data & Read(Size length, Size * size);

        virtual Data & ReadAsync(Size length, Size * size);

        virtual bool Close();
    };
}

#endif //CHOCO_CPP_CHANNEL_H
