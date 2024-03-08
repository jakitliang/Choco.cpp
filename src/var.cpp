//
// Created by liangjie on 2024/3/8.
//

#include "cc/var.h"

CC::Type<void *>::Type() : ptr(Pointer::Alloc<Object>(1)) {
    *ptr = Object();
}

CC::Type<void *>::Type(const Type & var) : ptr(Pointer::Retain<Object>(var.ptr)) {}

CC::Type<void *>::Type(Type && var) noexcept : ptr(Pointer::Retain<Object>(var.ptr)) {}

CC::Type<void *>::~Type() {
    Pointer::Release(ptr);
    ptr = nullptr;
}

CC::Object & CC::Type<void *>::operator*() { return *ptr; }

const CC::Object & CC::Type<void *>::operator*() const { return *ptr; }

CC::Object * CC::Type<void *>::operator->() { return ptr; }

const CC::Object * CC::Type<void *>::operator->() const { return ptr; }
