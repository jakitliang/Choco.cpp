//
// Created by liangjie on 2024/5/20.
//

#include "cc/error.h"
#include <cstring>

#ifdef _WIN32
#else
#include <cerrno>
#endif

CC::Error::Error() : From(SendFromSystem), Message{0} {
    Number = 0;
}

CC::Error & CC::Error::GetSystemError() {
    Number = errno;
    memset(&Message[0], 0, MessageLength);
    strerror_r(Number, &Message[0], MessageLength);

    return *this;
}

CC::Error & CC::Error::Reset() {
    Number = 0;

    return *this;
}

CC::Error CC::Error::SystemError() {
    return CC::Error().GetSystemError();
}
