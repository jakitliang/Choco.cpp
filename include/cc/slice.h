//
// Created by liangjie on 2024/3/8.
//

#ifndef CC_SLICE_H
#define CC_SLICE_H

#include "cc/var.h"
#include <initializer_list>

namespace CC {
    template<typename T>
    struct Variant<T []> {
        using Type = T(*)[];

        Type object;

        Variant() : object(Alloc(0)) {}

        Variant(const Variant<T []> & slice) : object(Retain(slice.object)) {}

        Variant(Variant<T []> && slice) : object(Retain(slice.object)) {}

        Variant(const Size & count) : object(Alloc(count)) {}

        template<Size S>
        Variant(const T (&arrRef)[S]) : object(Alloc(S)){
            for (int i = 0; i < S; ++i) {
                (*object)[i] = arrRef[i];
            }
        }

        template<Size S>
        Variant(T (&&arrRef)[S]) : object(Alloc(S)){
            for (int i = 0; i < S; ++i) {
                (*object)[i] = static_cast<T &&>(arrRef[i]);
            }
        }

        ~Variant() {
            Release(object);
            object = nullptr;
        }

        T * begin() {
            return &(*object)[0];
        }

        T * end() {
            return &(*object)[Pointer::Count(object)];
        }

        T & operator [](Size index) {
            return (*object)[index];
        }

        Size Count() const { return Pointer::Count(object); }

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
    using Slice = Variant<T []>;
}

#endif //CC_SLICE_H
