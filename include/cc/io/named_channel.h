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

        Size Read(void *data, Size length) override;

        Size ReadNonBlock(void *data, Size length) override;

        Size Write(const void *data, Size length) override;

        Size WriteNonBlock(const void *data, Size length) override;

        NamedChannel & operator=(const NamedChannel & namedChannel);

        NamedChannel & operator=(NamedChannel && namedChannel) noexcept;
    };
}

#endif //CHOCO_CPP_NAMED_CHANNEL_H
