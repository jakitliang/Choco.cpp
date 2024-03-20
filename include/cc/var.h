//
// Created by Jakit on 2024/3/18.
//

#ifndef CHOCO_CPP_VAR_H
#define CHOCO_CPP_VAR_H

#include "object.h"

namespace CC {
    template<typename T>
    struct Variant<T> : Variant<void> {
        using Type = T;

        Type * object;

        Variant() : object(Alloc<T>()) {}

        Variant(const Variant & v) : object(Retain(v.object)) {}

        Variant(Variant && v) : object(Retain(v.object)) {}

        Variant(const T & o) : object(*o) {}

        Variant(T && o) : object(static_cast<T &&>(o)) {}

        ~Variant() {
            Release(object);
        }

        Inspector & Inspect() {
            return reinterpret_cast<Inspector &>(*object);
        }

        Variant & operator=(const T & o) {
            *object = o;
        }

        Variant & operator=(T && o) {
            *object = static_cast<T &&>(o);
        }

        T & operator*() {
            return *object;
        }

        const T & operator*() const {
            return *object;
        }
    };

    template<typename T>
    using Var = Variant<T>;
}

#endif //CHOCO_CPP_VAR_H
