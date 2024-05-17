//
// Created by liangjie on 2024/5/17.
//

#ifndef CHOCO_CPP_TCP_CHANNEL_H
#define CHOCO_CPP_TCP_CHANNEL_H

#include "cc/io/channel.h"

namespace CC::IO {
    struct TCPChannel : IChannel, IChannelReader, IChannelWriter {
        struct Context;

        Context * context;

        TCPChannel();

        TCPChannel(const TCPChannel & tcpChannel);

        TCPChannel(TCPChannel && tcpChannel) noexcept;

        ~TCPChannel();

        bool Connect(const char * host, int port);

        virtual bool Close();

        virtual bool IsClosed();

        Size Read(void * data, Size length) override;

        Size ReadNonBlock(void * data, Size length) override;

        Size Write(const void * data, Size length) override;

        Size WriteNonBlock(const void * data, Size length) override;

        TCPChannel & operator=(const TCPChannel & tcpChannel);

        TCPChannel & operator=(TCPChannel && tcpChannel) noexcept;
    };
}

#endif //CHOCO_CPP_TCP_CHANNEL_H