//
// Created by liangjie on 2024/3/8.
//

#ifndef CC_SLICE_H
#define CC_SLICE_H

#include "cc/var.h"

namespace CC {
    template<typename T>
    struct Object<T []> {
        using Class = T(*)[];

        Class object;

        Object() : object(Alloc(0)) {}

        Object(const Object<T []> & slice) : object(Retain(slice.object)) {}

        Object(Object<T []> && slice) : object(Retain(slice.object)) {}

        Object(const Size & count) : object(Alloc(count)) {}

        ~Object() {
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

        static Class Alloc(Size count) {
            return static_cast<Class>(Pointer::Alloc(sizeof(T), count));
        }

        static Class Retain(Class object) {
            return static_cast<Class>(Pointer::Retain(object));
        }

        static Class ReAlloc(Class object, Size count) {
            return static_cast<Class>(Pointer::ReAlloc(object, count));
        }

        static bool Release(Class object) {
            return Pointer::Release(object);
        }
    };

    template<typename T>
    using Slice = Object<T []>;
}

#endif //CC_SLICE_H
