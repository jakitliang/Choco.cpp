//
// Created by liangjie on 2024/5/17.
//

#include "cc/io/tcp_channel.h"
#include "cc/zone.h"

struct CC::IO::TCPChannel::Context {

};

CC::IO::TCPChannel::TCPChannel() : context(CC::Make<Context>()) {}

CC::IO::TCPChannel::TCPChannel(const CC::IO::TCPChannel &tcpChannel)
    : context(CC::Retain(tcpChannel.context)) {}

CC::IO::TCPChannel::TCPChannel(CC::IO::TCPChannel &&tcpChannel) noexcept
    : context(tcpChannel.context) {
    tcpChannel.context = nullptr;
}

CC::IO::TCPChannel::~TCPChannel() {
    CC::Destroy(context);
}

CC::IO::TCPChannel &CC::IO::TCPChannel::operator=(const CC::IO::TCPChannel &tcpChannel) {
    if (this == &tcpChannel) return *this;

    CC::Destroy(context);
    context = CC::Retain(tcpChannel.context);

    return *this;
}

CC::IO::TCPChannel &CC::IO::TCPChannel::operator=(CC::IO::TCPChannel &&tcpChannel) noexcept {
    if (this == &tcpChannel) return *this;

    CC::Destroy(context);
    context = tcpChannel.context;
    tcpChannel.context = nullptr;

    return *this;
}
