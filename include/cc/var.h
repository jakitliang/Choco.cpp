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

        Variant() : object(std::is_abstract<Type>::value ? nullptr : Make<T>()) {}

        Variant(const Variant & v) : object(Retain(v.object)) {}

        Variant(Variant && v) : object(v.object) { v.object = nullptr; }

        Variant(const T & o) : object(Clone(o)) {}

        Variant(T && o) : object(Clone(static_cast<T &&>(o))) {}

        ~Variant() {
            Destroy(object);
        }

        Inspector & Inspect() {
            return reinterpret_cast<Inspector &>(*object);
        }

        Variant & operator=(const T & o) {
            Copy(object, 0, &o, 1);
        }

        Variant & operator=(T && o) {
            Move(object, 0, &o, 1);
        }

        T & operator*() {
            return *object;
        }

        const T & operator*() const {
            return *object;
        }

        template<typename D> bool is() {
            return std::is_base_of<typename RemoveAll<T>::Type, D>::value;
        }
    };

    template<typename T>
    using Var = Variant<T>;
}

#endif //CHOCO_CPP_VAR_H
