//
// Created by liangjie on 2024/3/8.
//

#ifndef CC_SLICE_H
#define CC_SLICE_H

#include "cc/object.h"
#include <iostream>

namespace CC {
    template<typename T, Size S>
    struct Variant<T [S]> : Variant<void> {
        using Type = T[S];

        Type * object;

        Variant() : object(reinterpret_cast<Type *>(Alloc<T>(S))) {}

        Variant(const Variant & slice) : object(reinterpret_cast<Type *>(Retain(slice.object))) {}

        Variant(Variant && slice) : object(reinterpret_cast<Type *>(Retain(slice.object))) {}

        template<Size SS>
        Variant(const T (&array)[SS]) : object(reinterpret_cast<Type *>(Alloc<T>(S))) {
            Copy<T>(reinterpret_cast<T *>(object), 0, &array[0], S > SS ? SS : S);
        }

        template<Size SS>
        Variant(T (&&array)[SS]) : object(reinterpret_cast<Type *>(Alloc<T>(S))){
            Move<T>(reinterpret_cast<T *>(object), 0, &array[0], S > SS ? SS : S);
        }

        ~Variant() {
            Release(reinterpret_cast<T *>(object));
        }

        CC::Size Count() { return CC::Count<T>(object); }

        CC::Size Count() const { return CC::Count<T>(object); }

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
            CopyConstruct<T>(reinterpret_cast<T *>(slice.object),
                             0,
                             reinterpret_cast<T *>(object),
                             S);
            CopyConstruct<T>(reinterpret_cast<T *>(slice.object),
                             S,
                             reinterpret_cast<const T *>(rhs.object),
                             SS);
            return slice;
        }

        template<Size SS>
        Variant<T [S + SS]> operator+(const T (&rhs)[SS]) const {
            Variant<T [S + SS]> slice;
            CopyConstruct<T>(reinterpret_cast<T *>(slice.object),
                             0,
                             reinterpret_cast<T *>(object),
                             S);
            CopyConstruct<T>(reinterpret_cast<T *>(slice.object),
                             S,
                             reinterpret_cast<const T *>(&rhs[0]),
                             SS);
            return slice;
        }

        Inspector & Inspect() {
            return reinterpret_cast<Inspector &>(*object);
        }
    };

    template<typename T, Size S>
    using Slice = Variant<T [S]>;
}

#endif //CC_SLICE_H
