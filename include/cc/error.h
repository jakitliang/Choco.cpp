//
// Created by liangjie on 2024/5/20.
//

#ifndef CHOCO_CPP_ERROR_H
#define CHOCO_CPP_ERROR_H

#include "cc/types.h"

namespace CC {
    struct Error {
        typedef CC_ENUM(Byte, SendFrom) {
            SendFromSystem,
            SendFromUser
        };

        static const int MessageLength = 1024;

        SendFrom From;
        int Number;
        char Message[MessageLength];

        Error();

        Error & GetSystemError();

        Error & Reset();

        static Error SystemError();

        static Error Default;
    };
}

#endif //CHOCO_CPP_ERROR_H
