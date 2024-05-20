//
// Created by liangjie on 2024/5/20.
//

#ifndef CHOCO_CPP_IO_SOCKET_H
#define CHOCO_CPP_IO_SOCKET_H

#include "cc/types.h"
#include "cc/error.h"
#include "cc/zone.h"

namespace CC::IO {
    struct Socket {
        typedef CC_ENUM(int, Protocol) {
            ProtocolTCP,
            ProtocolUDP,
        };

        typedef CC_ENUM(int, Return) {
            ReturnError = -1, // Return with errno
            ReturnOK = 0,
            ReturnFailed = 1
        };

        struct Context;

        friend CC::IO::Socket * CC::Make<CC::IO::Socket>();

        bool IsNonBlock;
        bool IsShutdown;
        Property<Context, 128> context;

        ~Socket();

        bool TCP();

        bool UDP();

        Return Connect(const char *host, UInt64 port);

        Return ConnectNonBlock(const char *host, UInt64 port);

        Return Bind(const char *host, UInt64 port);

        Return Listen(Int32 queue);

        bool Accept(Socket *clientSocket);

        bool AcceptNonBlock(Socket *clientSocket);

        Int64 Receive(void *buffer, UInt64 size);

        Int64 ReceiveNonBlock(void *buffer, UInt64 size);

        Int64 ReceiveFrom(const char *address, UInt64 port, void *buffer, UInt64 size);

        Int64 ReceiveFromNonBlock(const char *address, UInt64 port, void *buffer, UInt64 size);

        Int64 Send();

        bool Close();

        bool SetBlock();

        bool SetNonBlock();

        Protocol GetProtocol();

        bool IsClosed();

    private:
        Socket();
    };
}

#endif //CHOCO_CPP_IO_SOCKET_H
