//
// Created by liangjie on 2024/3/8.
//

#ifndef CC_SLICE_H
#define CC_SLICE_H

#include "cc/var.h"

namespace CC {
    template<typename T>
    struct Variant<T []> {
        using Type = T(*)[];

        Type object;

        Variant() : object(Alloc(0)) {}

        Variant(const Variant<T []> & slice) : object(Retain(slice.object)) {}

        Variant(Variant<T []> && slice) : object(Retain(slice.object)) {}

        Variant(const Size & count) : object(Alloc(count)) {}

        ~Variant() {
            Release(object);
            object = nullptr;
        }

        T * begin() {
            return object;
        }

        T * end() {
            return Pointer::Element(object, Pointer::Count(object));
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
