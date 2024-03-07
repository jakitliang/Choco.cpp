//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CC_NUMERIC_H
#define CC_NUMERIC_H

#include "cc/defines.h"

namespace CC {
    using Int8 = char;
    using UInt8 = unsigned char;
    using Int16 = short;
    using UInt16 = unsigned short;
    using Int32 = int;
    using UInt32 = unsigned int;
    using Int64 = long long;
    using UInt64 = unsigned long long;
    using Byte = UInt8;

#ifdef CC_64
    using Size = unsigned long long;
#else
    using Size = unsigned int;
#endif
}

#endif //CC_NUMERIC_H
