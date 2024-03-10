//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#ifndef CC_VAR_H
#define CC_VAR_H

#include "cc/pointer.h"

namespace CC {
    template<typename T>
    struct Variant<T *> {
        using Type = T *;
        using ImmutableType = const T *;

        Type object;

        Variant() : object(Alloc(1)) {
            *object = T();
        }

        Variant(const Variant & o) : object(Retain(o.object)) {}

        Variant(Variant && o) noexcept : object(Retain(o.object)) {}

        ~Variant() {
            Pointer::Release(object);
            object = nullptr;
        }

        T & operator*() { return *object; }

        const T & operator*() const { return *object; }

        T * operator->() { return object; }

        const T * operator->() const { return object; }

        // Static methods for lifecycle

        static Type Alloc(Size count) {
            return static_cast<Type>(Pointer::Alloc(sizeof(T), count));
        }

        static Type Retain(Type object) {
            return static_cast<Type>(Pointer::Retain(object));
        }

        static Type ReAlloc(Type object, Size count) {
            return static_cast<Type>(Pointer::ReAlloc(object, count));
        }

        static bool Release(Type object) {
            return Pointer::Release(object);
        }
    };

    template<typename T>
    using Var = Variant<T *>;
}

#endif //CC_VAR_H
