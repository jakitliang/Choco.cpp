//
// Created by Jakit Liang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_SLICE_H
#define CC_SLICE_H

#include "cc/var.h"
#include <iostream>

namespace CC {
    template<typename T, Size S>
    struct Variant<T [S]> : Variant<void> {
        using Type = T[S];

        Type * object;

        Variant() : object(reinterpret_cast<Type *>(Make<T>(S))) {}

        Variant(const Variant & slice) : object(reinterpret_cast<Type *>(Retain(slice.object))) {}

        Variant(Variant && slice) : object(reinterpret_cast<Type *>(slice.object)) {
            slice.object = nullptr;
        }

        Variant(const T (&array)[S]) : object(reinterpret_cast<Type *>(Clone(array))) {}

        Variant(T (&&array)[S]) : object(reinterpret_cast<Type *>(Clone(static_cast<T (&&)[S]>(array)))) {}

        ~Variant() {
            Destroy(reinterpret_cast<T *>(object));
        }

        CC::Size Count() const { return S; }

        T * begin() {
            return &(*object)[0];
        }

        T * end() {
            return &(*object)[Count()];
        }

        T & operator [](Size index) {
            return (*object)[index];
        }

        const T & operator [](Size index) const {
            return (*object)[index];
        }

        template<Size SS>
        Variant<T [S + SS]> operator+(const Variant<T [SS]> & rhs) const {
            Variant<T [S + SS]> slice;
            Copy<T>(reinterpret_cast<T *>(slice.object),
                             0,
                             reinterpret_cast<T *>(object),
                             S);
            Copy<T>(reinterpret_cast<T *>(slice.object),
                             S,
                             reinterpret_cast<const T *>(rhs.object),
                             SS);
            return slice;
        }

        template<Size SS>
        Variant<T [S + SS]> operator+(const T (&rhs)[SS]) const {
            Variant<T [S + SS]> slice;
            Copy<T>(reinterpret_cast<T *>(slice.object),
                             0,
                             reinterpret_cast<T *>(object),
                             S);
            Copy<T>(reinterpret_cast<T *>(slice.object),
                             S,
                             reinterpret_cast<const T *>(&rhs[0]),
                             SS);
            return slice;
        }

        Inspector & Inspect() {
            return reinterpret_cast<Inspector &>(*object);
        }

        template<Size P1, Size P2>
        Variant<T [P2 - P1]> Range() const {
            static_assert(P2 > P1, "Illegal range");
            static_assert(P2 <= S, "Illegal range");
            Variant<T [P2 - P1]> slice;
            Copy<T>(reinterpret_cast<T *>(slice.object),
                    0,
                    reinterpret_cast<T *>(object) + P1,
                    P2 - P1);
            return slice;
        }
    };

    template<typename T, Size S>
    Variant<T [S]> Slice(T (&&array)[S]) {
        return {array};
    }
}

#endif //CC_SLICE_H
