//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#ifndef CHOCO_CPP_CHANNEL_H
#define CHOCO_CPP_CHANNEL_H

#include "cc/types.h"
#include "cc/error.h"

namespace CC::IO {
    typedef CC_ENUM(int, Result) {
        ROK = 0
    };

    struct IChannelEvent;
    struct IChannelReaderEvent;
    struct IChannelWriterEvent;

    struct IChannel {
        virtual bool Close() = 0;

        virtual bool IsClosed() = 0;
    };

    struct IChannelReader {
        virtual Result Read(void * data, Size length, Size * bytesRead) = 0;

        virtual Result ReadNonBlock(void * data, Size length, Size * bytesRead) = 0;
    };

    struct IChannelWriter {
        virtual Result Write(const void * data, Size length, Size * bytesWritten) = 0;

        virtual Result WriteNonBlock(const void * data, Size length, Size * bytesWritten) = 0;
    };

    struct IChannelEvent {
        virtual void onOpen(IChannel & channel) = 0;

        virtual void onClose(IChannel & channel) = 0;
    };

    struct IChannelReaderEvent {
        virtual Size onRead(IChannel & channel, void * data, Size length) = 0;
    };

    struct IChannelWriterEvent {
        virtual void onWrite(IChannel & channel, Size length) = 0;
    };
}

#endif //CHOCO_CPP_CHANNEL_H
