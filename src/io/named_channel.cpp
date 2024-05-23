//
// Created by liangjie on 2024/5/21.
//

#include "cc/io/named_channel.h"
#include "cc/zone.h"

#ifdef _WIN32
extern "C" {
#include <io.h>
#include <fcntl.h>
}
#else
extern "C" {
#include <fcntl.h>
#include <unistd.h>
}
#endif

#define INVALID (-1)

using R = CC::IO::Result;

struct CC::IO::NamedChannel::Context {
    int FD;

    Context() : FD(INVALID) {}

    ~Context() {
        if (FD != INVALID) close(FD);
        FD = INVALID;
    }
};

CC::IO::NamedChannel::NamedChannel() : context(CC::Make<Context>()) {}

CC::IO::NamedChannel::NamedChannel(const CC::IO::NamedChannel &namedChannel)
    : context(CC::Retain(namedChannel.context)) {}

CC::IO::NamedChannel::NamedChannel(CC::IO::NamedChannel &&namedChannel) noexcept
    : context(namedChannel.context) {
    namedChannel.context = nullptr;
}

CC::IO::NamedChannel::~NamedChannel() { {
    CC::Destroy<Context>(context);
}}

bool CC::IO::NamedChannel::Open(const char *path, CC::IO::NamedChannel::Target target) {
    if (context->FD != INVALID) return true;

    int fd;
    int flags = (target == TargetIn) ? O_RDONLY : (O_WRONLY | O_CREAT);

#ifdef _WIN32
    _sopen_s(&fd, path, flags, _SH_DENYNO, _S_IREAD | _S_IWRITE);
#else
    fd = open(path, flags);
#endif

    if (fd == -1) return false;

    context->FD = fd;

    return true;
}

bool CC::IO::NamedChannel::Close() {
    if (context->FD == INVALID) return false;

    close(context->FD);

    context->FD = INVALID;

    return true;
}

bool CC::IO::NamedChannel::IsClosed() {
    return context->FD == INVALID;
}

CC::IO::Result CC::IO::NamedChannel::Read(void *data, CC::Size length, Size * bytesRead) {
#ifdef _WIN32
    auto ret = _read(context->FD, data, length);
#else
    auto ret = read(context->FD, data, length);
#endif

    return ret >= 0 ? R::EOF : R::Error;
}

CC::IO::Result CC::IO::NamedChannel::ReadNonBlock(void *data, CC::Size length, Size * bytesRead) {
    return Read(data, length, bytesRead);
}

CC::IO::Result CC::IO::NamedChannel::Write(const void *data, CC::Size length, Size * bytesRead) {
#ifdef _WIN32
    auto ret = _write(context->FD, data, length);
#else
    auto ret = write(context->FD, data, length);
#endif

    return ret == -1 ? R::Error : R::OK;
}

CC::IO::Result CC::IO::NamedChannel::WriteNonBlock(const void *data, CC::Size length, Size * bytesRead) {
    return Write(data, length, bytesRead);
}

CC::IO::NamedChannel &CC::IO::NamedChannel::operator=(const CC::IO::NamedChannel &namedChannel) {
    if (this == &namedChannel) return *this;

    CC::Destroy<Context>(context);
    context = CC::Retain(namedChannel.context);

    return *this;
}

CC::IO::NamedChannel &CC::IO::NamedChannel::operator=(CC::IO::NamedChannel &&namedChannel) noexcept {
    if (this == &namedChannel) return *this;

    CC::Destroy<Context>(context);
    context = namedChannel.context;
    namedChannel.context = nullptr;

    return *this;
}

