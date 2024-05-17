//
// Created by liangjie on 2024/5/17.
//

#ifndef CHOCO_CPP_UDP_CHANNEL_H
#define CHOCO_CPP_UDP_CHANNEL_H

#include "cc/io/channel.h"

namespace CC::IO {
    struct UDPChannel : IChannel, IChannelReader, IChannelWriter {
        struct Context;

        Context * context;

        UDPChannel();

        UDPChannel(const UDPChannel & udpChannel);

        UDPChannel(UDPChannel && udpChannel) noexcept;

        ~UDPChannel();

        bool Connect(const char * host, int port);

        virtual bool Close();

        virtual bool IsClosed();

        Size Read(void * data, Size length) override;

        Size ReadNonBlock(void * data, Size length) override;

        Size Write(const void * data, Size length) override;

        Size WriteNonBlock(const void * data, Size length) override;

        UDPChannel & operator=(const UDPChannel & udpChannel);

        UDPChannel & operator=(UDPChannel && udpChannel) noexcept;
    };
}

#endif //CHOCO_CPP_UDP_CHANNEL_H
