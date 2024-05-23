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

#ifdef _WIN32
    strerror_s(Message, MessageLength, Number);
#else
    strerror_r(Number, &Message[0], MessageLength);
#endif



    return *this;
}

CC::Error & CC::Error::Reset() {
    Number = 0;

    return *this;
}

CC::Error CC::Error::SystemError() {
    return CC::Error().GetSystemError();
}
