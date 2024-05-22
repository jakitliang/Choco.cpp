//
// Created by liangjie on 2024/5/21.
//

#ifndef CHOCO_CPP_NAMED_CHANNEL_H
#define CHOCO_CPP_NAMED_CHANNEL_H

#include "cc/io/channel.h"

namespace CC::IO {
    struct NamedChannel : IChannel, IChannelReader, IChannelWriter {
        typedef CC_ENUM(int, Target) {
            TargetIn,
            TargetOut
        };

        struct Context;

        Context * context;

        NamedChannel();

        NamedChannel(const NamedChannel & namedChannel);

        NamedChannel(NamedChannel && namedChannel) noexcept;

        ~NamedChannel();

        bool Open(const char *path, Target target);

        bool Close() override;

        bool IsClosed() override;

        Result Read(void * data, Size length, Size * bytesRead) override;

        Result ReadNonBlock(void * data, Size length, Size * bytesRead) override;

        Result Write(const void * data, Size length, Size * bytesWritten) override;

        Result WriteNonBlock(const void * data, Size length, Size * bytesWritten) override;

        NamedChannel & operator=(const NamedChannel & namedChannel);

        NamedChannel & operator=(NamedChannel && namedChannel) noexcept;
    };
}

#endif //CHOCO_CPP_NAMED_CHANNEL_H
