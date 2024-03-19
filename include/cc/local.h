//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#ifndef CC_VAR_H
#define CC_VAR_H

#include "cc/object.h"

namespace CC {
    template<typename T>
    struct Variant<T &> : Variant<void> {
        using Type = T;
        using ImmutableType = const T;

        Type & object;

        Variant() : object(Make<T>()) {}

        Variant(const Variant & v) : object(Retain(v.object)) {}

        Variant(Variant && v) : object(Retain(v.object)) {}

        Variant(const T & o) {
            object = o;
        }

        Variant(T && o) {
            object = static_cast<T &&>(o);
        }

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

    template<typename T>
    using Local = Variant<T &>;
}

#endif //CC_VAR_H
