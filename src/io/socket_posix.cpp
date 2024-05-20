//
// Created by liangjie on 2024/5/20.
//

#include "cc/io/socket.h"
#include <new>
#include <cstring>

extern "C" {
#include <sys/fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
}

#define ILLEGAL_FD (-1)

struct CC::IO::Socket::Context {
    int FD;
    sockaddr_in Address;
};

CC::IO::Socket::Socket() : context() {
    IsNonBlock = false;
    IsShutdown = false;
    context->FD = ILLEGAL_FD;
    memset(&context->Address, 0, sizeof(sockaddr_in));
}

CC::IO::Socket::~Socket() {

}

bool CC::IO::Socket::TCP() {
    if (context->FD >= 0) return true;

    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (fd == ILLEGAL_FD) {
        return false;
    }

    context->FD = fd;

    return true;
}

bool CC::IO::Socket::UDP() {
    if (context->FD >= 0) return true;

    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (fd == ILLEGAL_FD) {
        return false;
    }

    context->FD = fd;

    return true;
}

CC::IO::Socket::Return CC::IO::Socket::Connect(const char *host, CC::UInt64 port) {
    if (context->FD == ILLEGAL_FD) return CC::IO::Socket::ReturnFailed;

    context->Address.sin_family = AF_INET;
    context->Address.sin_addr.s_addr = inet_addr(host);
    context->Address.sin_port = htons(port);

    return connect(context->FD,
                   reinterpret_cast<sockaddr *>(&context->Address),
                   sizeof(context->Address));
}

CC::IO::Socket::Return CC::IO::Socket::ConnectNonBlock(const char *host, CC::UInt64 port) {
    if (context->FD == ILLEGAL_FD) return CC::IO::Socket::ReturnFailed;

    context->Address.sin_family = AF_INET;
    context->Address.sin_addr.s_addr = inet_addr(host);
    context->Address.sin_port = htons(port);

    SetNonBlock();
    auto ret = connect(context->FD,
                       reinterpret_cast<sockaddr *>(&context->Address),
                       sizeof(context->Address));
    SetBlock();
    return ret;
}

CC::IO::Socket::Return CC::IO::Socket::Bind(const char *host, CC::UInt64 port) {
    if (context->FD == ILLEGAL_FD) return CC::IO::Socket::ReturnFailed;

    context->Address.sin_family =  AF_INET;
    context->Address.sin_addr.s_addr = inet_addr(host);
    context->Address.sin_port = htons(port);

    return bind(context->FD, reinterpret_cast<sockaddr *>(&context->Address), sizeof(context->Address));
}

CC::IO::Socket::Return CC::IO::Socket::Listen(CC::Int32 queue) {
    if (context->FD == ILLEGAL_FD) return CC::IO::Socket::ReturnFailed;

    return listen(context->FD, queue);
}

bool CC::IO::Socket::Close() {
    if (context->FD == ILLEGAL_FD) return true;

    auto fd = context->FD;
    context->FD = ILLEGAL_FD;

    return close(fd) == 0;
}

bool CC::IO::Socket::SetBlock() {
    if (context->FD == ILLEGAL_FD) return false;

    int flags = fcntl(context->FD, F_GETFL, 0);
    flags &= (~(O_NONBLOCK));
    fcntl(context->FD, F_SETFL, flags);
    IsNonBlock = false;

    return true;
}

bool CC::IO::Socket::SetNonBlock() {
    if (context->FD == ILLEGAL_FD) return false;

    int flags = fcntl(context->FD, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(context->FD, F_SETFL, flags);
    IsNonBlock = true;

    return true;
}

bool CC::IO::Socket::IsClosed() {
    return context->FD >= 0 ? false : true;
}
