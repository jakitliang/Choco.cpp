//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#ifndef CC_VAR_H
#define CC_VAR_H

#include "cc/value.h"
#include "cc/pointer.h"

namespace CC {
    template<>
    struct Type<void *> : Object {
        Object * ptr;

        Type() : ptr(Pointer::Alloc<Object>(1)) {
            *ptr = Object();
        }

        Type(const Type & var) : ptr(Pointer::Retain<Object>(var.ptr)) {}

        Type(Type && var) : ptr(Pointer::Retain<Object>(var.ptr)) {}

        ~Type() {
            Pointer::Release(ptr);
            ptr = nullptr;
        }

        Object & operator*() { return *ptr; }

        const Object & operator*() const { return *ptr; }

        Object * operator->() { return ptr; }

        const Object * operator->() const { return ptr; }
    };

    template<typename T>
    struct Type<T *> : Object {
        Type<T> * ptr;

        Type() : ptr(Pointer::Alloc<Type<T>>(1)) {
            *ptr = Type<T>();
        }

        Type(const Type & var) : ptr(Pointer::Retain<Type<T>>(var.ptr)) {}

        Type(Type && var) : ptr(Pointer::Retain<Type<T>>(var.ptr)) {}

        ~Type() {
            Pointer::Release(ptr);
            ptr = nullptr;
        }

        T & operator*() { return ptr->value; }

        const T & operator*() const { return ptr->value; }

        T * operator->() { return &ptr->value; }

        const T * operator->() const { return ptr->value; }
    };

    template<typename T>
    using Var = Type<T *>;
}

#endif //CC_VAR_H
