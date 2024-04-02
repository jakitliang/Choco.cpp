//
// Created by Jakit on 2024/4/2.
//

#ifndef CHOCO_CPP_ANY_H
#define CHOCO_CPP_ANY_H

#include "cc/variant.h"
#include "cc/zone.h"

namespace CC {
    template<>
    struct Var<void> {
        using Type = void;
        using Finalizer = Zone::Finalizer;

        Type * object;
        Finalizer finalizer;

        Var() : object(nullptr), finalizer(nullptr) {}

        Var(const Var & v) : object(Retain(v.object)), finalizer(v.finalizer) {}

        Var(Var && v) : object(v.object), finalizer(v.finalizer) {
            v.object = nullptr;
            v.finalizer = nullptr;
        }

        ~Var() {
            if (finalizer) {
                Zone::Release(object, finalizer);

            } else {
                Release(object);
            }
        }

        Var & operator=(const Var & var) {
            if (this == &var) return *this;

            if (finalizer) {
                Zone::Release(object, finalizer);

            } else {
                Release(object);
            }

            object = Retain(var.object);

            return *this;
        }

        Var & operator=(Var && var) {
            if (this == &var) return *this;

            if (finalizer) {
                Zone::Release(object, finalizer);

            } else {
                Release(object);
            }

            object = var.object;
            var.object = nullptr;

            return *this;
        }

        template<typename T>
        T * & To() {
            return reinterpret_cast<T *>(object);
        }
    };

    using Any = Var<void>;
}

#endif //CHOCO_CPP_ANY_H
