//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/5.
//

#include "cc/intptr.h"

// IntPtr Implementation

CC::IntPtr::IntPtr(const CC::IntPtr::Address &addr) {
    address = addr;
}

CC::IntPtr::IntPtr(void *const &p) {
    address = reinterpret_cast<Address>(p);
}

CC::IntPtr &CC::IntPtr::operator=(const CC::IntPtr::Address &addr) {
    address = addr;
    return *this;
}

CC::IntPtr &CC::IntPtr::operator=(void *const &p) {
    address = reinterpret_cast<Address>(p);
    return *this;
}

CC::IntPtr::operator Address() const {
    return address;
}

CC::IntPtr::operator void *() {
    return reinterpret_cast<void *>(address);
}

CC::IntPtr::operator const void *() const {
    return reinterpret_cast<const void *>(address);
}

// UIntPtr Implementation

CC::UIntPtr::UIntPtr(const CC::UIntPtr::Address &addr) {
    address = addr;
}

CC::UIntPtr::UIntPtr(void *const &p) {
    address = reinterpret_cast<Address>(p);
}

CC::UIntPtr::UIntPtr(const void *const &p) {
    address = reinterpret_cast<Address>(p);
}

CC::UIntPtr &CC::UIntPtr::operator=(const CC::UIntPtr::Address &addr) {
    address = addr;
    return *this;
}

CC::UIntPtr &CC::UIntPtr::operator=(void *const &p) {
    address = reinterpret_cast<Address>(p);
    return *this;
}

CC::UIntPtr::operator Address() const {
    return address;
}

CC::UIntPtr::operator void *() {
    return reinterpret_cast<void *>(address);
}

CC::UIntPtr::operator const void *() const {
    return reinterpret_cast<const void *>(address);
}
