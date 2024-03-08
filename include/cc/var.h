//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#ifndef CC_VAR_H
#define CC_VAR_H

#include "cc/pointer.h"

namespace CC {
    template<typename T>
    struct Object<T *> {
        using Class = T *;
        using ImmutableClass = const T *;

        Class object;

        Object() : object(Alloc(1)) {
            *object = T();
        }

        Object(const Object & o) : object(Retain(o.object)) {}

        Object(Object && o) noexcept : object(Retain(o.object)) {}

        ~Object() {
            Pointer::Release(object);
            object = nullptr;
        }

        T & operator*() { return *object; }

        const T & operator*() const { return *object; }

        T * operator->() { return object; }

        const T * operator->() const { return object; }

        // Static methods for lifecycle

        static Class Alloc(Size count) {
            return static_cast<Class>(Pointer::Alloc(sizeof(T), count));
        }

        static Class Retain(Class object) {
            return static_cast<Class>(Pointer::Retain(object));
        }

        static Class ReAlloc(Class object, Size count) {
            return static_cast<Class>(Pointer::ReAlloc(object, count));
        }

        static bool Release(Class object) {
            return Pointer::Release(object);
        }
    };

    template<typename T>
    using Var = Object<T *>;
}

#endif //CC_VAR_H
