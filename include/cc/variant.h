//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/6.
//

#ifndef CC_VARIANT_H
#define CC_VARIANT_H

#include "cc/object.h"

namespace CC {
    template<typename T>
    struct Variant : Variant<void> {
        using Type = T;
        using ImmutableType = const T;

        Type & object;

        Variant() : object(Alloc<T>()) {}

        Variant(const Variant & v) : object(Retain(v.object)) {}

        Variant(Variant && v) : object(Retain(v.object)) {}

        Variant(const T & o) : object(o) {}

        Variant(T && o) : object(static_cast<T &&>(o)) {}

        ~Variant() {
            Release(object, true);
        }

        Inspector & Inspect() {
            return reinterpret_cast<Inspector &>(object);
        }

        Variant & operator=(const T & o) {
            object = o;
        }

        Variant & operator=(T && o) {
            object = static_cast<T &&>(o);
        }

        T & operator*() {
            return object;
        }

        const T & operator*() const {
            return object;
        }
    };
}

#endif //CC_VARIANT_H
