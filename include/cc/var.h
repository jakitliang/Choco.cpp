//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/18.
//

#ifndef CHOCO_CPP_VAR_H
#define CHOCO_CPP_VAR_H

#include "object.h"

namespace CC {
    template<typename T>
    struct Var : Var<void> {
        using Type = T;

        Type * object;

        Var() : object(std::is_abstract<Type>::value ? nullptr : Make<T>()) {}

        Var(const Var & v) : object(Retain(v.object)) {}

        Var(Var && v) : object(v.object) { v.object = nullptr; }

        Var(const T & o) : object(Clone(o)) {}

        Var(T && o) : object(Clone(static_cast<T &&>(o))) {}

        ~Var() {
            Destroy(object);
        }

        Var & operator=(const Var & var) {
            if (this == &var) return *this;

            Destroy(object);
            object = Retain(var.object);

            return *this;
        }

        Var & operator=(Var && var) {
            if (this == &var) return *this;

            Destroy(object);
            object = var.object;
            var.object = nullptr;

            return *this;
        }

        Var & operator=(const T & o) {
            Copy(object, 0, &o, 1);
        }

        Var & operator=(T && o) {
            Move(object, 0, &o, 1);
        }

        T & operator*() {
            return *object;
        }

        const T & operator*() const {
            return *object;
        }

        T * operator->() {
            return object;
        }

        const T * operator->() const {
            return object;
        }

        template<typename D> bool Is() {
            return std::is_base_of<typename Decay<T>::Type, D>::value;
        }
    };
}

#endif //CHOCO_CPP_VAR_H
