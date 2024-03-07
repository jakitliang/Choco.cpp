//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CC_INTPTR_H
#define CC_INTPTR_H

#include "cc/defines.h"

namespace CC {
    struct IntPtr {
#ifdef CC_64
        using Address = long long;
#else
        using Address = int;
#endif
        Address address;

        IntPtr() = default;

        IntPtr(const Address & addr);

        IntPtr(void * const & p);

        IntPtr & operator=(const Address & addr);

        IntPtr & operator=(void * const & p);

        operator Address() const;

        operator void *();

        operator const void *() const;
    };

    struct UIntPtr {
#ifdef CC_64
        using Address = unsigned long long;
#else
        using Address = unsigned int;
#endif
        Address address;

        UIntPtr() = default;

        UIntPtr(const Address & addr);

        UIntPtr(void * const & p);

        UIntPtr(const void * const & p);

        UIntPtr & operator=(const Address & addr);

        UIntPtr & operator=(void * const & p);

        operator Address() const;

        operator void *();

        operator const void *() const;
    };
}

#endif //CC_INTPTR_H
