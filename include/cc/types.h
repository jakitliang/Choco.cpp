//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CC_TYPES_H
#define CC_TYPES_H

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

#if defined(_WINDOWS)
#if defined(_WIN64)
    using Size = unsigned long long;
#elif defined(_WIN32)
    using Size = unsigned int;
#endif
#elif defined(__SIZE_TYPE__)
    using Size = __SIZE_TYPE__;
#endif

    template<class T> struct Decay { typedef T Type; };
    template<class T> struct Decay<T*> : Decay<T> {};
    template<class T> struct Decay<T&> : Decay<T> {};
    template<class T> struct Decay<T&&> : Decay<T> {};
    template<class T> struct Decay<T const> : Decay<T> {};
    template<class T> struct Decay<T volatile> : Decay<T> {};
    template<class T> struct Decay<T const volatile> : Decay<T> {};
    template<class T> struct Decay<T[]> : Decay<T> {};
    template<class T, int N> struct Decay<T[N]> : Decay<T> {};
}

#endif //CC_TYPES_H
