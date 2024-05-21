//
// Created by liangjie on 2024/5/17.
//

#include "cc/io/udp_channel.h"
#include "cc/zone.h"
#include <cstring>

struct CC::IO::UDPChannel::Context {
    ssize_t z;
};

CC::IO::UDPChannel::UDPChannel() : context(CC::Make<Context>()) {}

CC::IO::UDPChannel::UDPChannel(const CC::IO::UDPChannel &udpChannel)
    : context(CC::Retain(udpChannel.context)) {}

CC::IO::UDPChannel::UDPChannel(CC::IO::UDPChannel &&udpChannel) noexcept
    : context(udpChannel.context) {
    udpChannel.context = nullptr;
}

CC::IO::UDPChannel::~UDPChannel() {
    CC::Destroy(context);
}

bool CC::IO::UDPChannel::Connect(const char *host, int port) {

}

CC::IO::UDPChannel &CC::IO::UDPChannel::operator=(const CC::IO::UDPChannel &udpChannel) {
    if (this == &udpChannel) return *this;

    CC::Destroy(context);
    context = CC::Retain(udpChannel.context);

    return *this;
}

CC::IO::UDPChannel &CC::IO::UDPChannel::operator=(CC::IO::UDPChannel &&udpChannel) noexcept {
    if (this == &udpChannel) return *this;

    CC::Destroy(context);
    context = udpChannel.context;
    udpChannel.context = nullptr;

    return *this;
}


