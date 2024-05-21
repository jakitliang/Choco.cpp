//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CHOCO_CPP_TYPES_H
#define CHOCO_CPP_TYPES_H

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
    using Float32 = float;
    using Float64 = double;

#if defined(_WINDOWS)
#if defined(_WIN64)
    using Size = unsigned long long;
    using SSize = long long;
#elif defined(_WIN32)
    using Size = unsigned int;
    using SSize = int;
#endif
#else
    using Size = unsigned long;
    using SSize = long;
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

    template<typename T, typename F>
    T To(const F & from);

    template <typename T, unsigned long N = sizeof(T)>
    struct Property {
        T * operator->() {
            return reinterpret_cast<T *>(data);
        }

        const T * operator->() const {
            return reinterpret_cast<const T *>(data);
        }

        T & operator*() {
            return *reinterpret_cast<T *>(data);
        }

        const T & operator*() const {
            return *reinterpret_cast<const T *>(data);
        }

        CC_ALIGN_DECL(8, Byte data[N]);
    };
}

#endif //CHOCO_CPP_TYPES_H
