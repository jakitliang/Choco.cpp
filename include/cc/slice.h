//
// Created by liangjie on 2024/3/8.
//

#ifndef CC_SLICE_H
#define CC_SLICE_H

#include "cc/object.h"
#include <iostream>

namespace CC {
    template<typename T>
    struct Variant<T (&)[]> : Variant<void> {
        using Type = T[];

        Type & object;

        Variant() : object(*reinterpret_cast<T (*)[]>(Zone::Alloc<T>(0))) {}

        Variant(const Variant<T []> & slice) : object(Retain(slice.object)) {}

        Variant(Variant<T []> && slice) : object(Retain(slice.object)) {}

        Variant(const Size & count) : object(*reinterpret_cast<Type *>(Zone::Alloc<T>(count))) {
            for (int i = 0; i < count; ++i) {
                new (&object[i]) T();
            }
        }

        template<Size S>
        Variant(const T (&array)[S]) : object(*reinterpret_cast<Type *>(Zone::Alloc<T>(S))){
            for (int i = 0; i < S; ++i) {
                new (&object[i]) T(array[i]);
            }
        }

        template<Size S>
        Variant(T (&&array)[S]) : object(*reinterpret_cast<Type *>(Zone::Alloc<T>(S))){
            for (int i = 0; i < S; ++i) {
                new (&object[i]) T(static_cast<T &&>(array[i]));
            }
        }

        Variant(const Variant<T []> & s1, const Variant<T []> & s2)
            : object(*reinterpret_cast<Type *>(Zone::Alloc<T>(s1.Count() + s2.Count()))) {
            int i = 0;
            for (int j = 0; j < s1.Count(); ++i, ++j) {
                new (&object[i]) T(s1[j]);
            }
            for (int j = 0; j < s2.Count(); ++i, ++j) {
                new (&object[i]) T(s2[j]);
            }
        }

        template<Size S>
        Variant(const Variant<T []> & s1, const T (&&array)[S])
                : object(*reinterpret_cast<Type *>(Zone::Alloc<T>(s1.Count() + S))) {
            int i = 0;
            for (int j = 0; j < s1.Count(); ++i, ++j) {
                new (&object[i]) T(s1[j]);
            }
            for (int j = 0; j < S; ++i, ++j) {
                new (&object[i]) T(array[j]);
            }
        }

        ~Variant() {
            Release(object, [](Type & t) {
                auto count = CC::Count<T>(t);
                for (int i = 0; i < count; ++i) {
                    t[i].~T();
                }
            });
        }

        CC::Size Count() { return CC::Count<T>(object); }

        CC::Size Count() const { return CC::Count<T>(object); }

        T * begin() {
            return &object[0];
        }

        T * end() {
            return &object[Count()];
        }

        T & operator [](Size index) {
            return object[index];
        }

        const T & operator [](Size index) const {
            return object[index];
        }

        Variant operator+(const Variant & rhs) const {
            return {*this, rhs};
        }

        template<Size S>
        Variant operator+(const T (&rhs)[S]) const {
            return {*this, rhs};
        }

        Inspector & Inspect() {
            return reinterpret_cast<Inspector &>(object);
        }
    };

    template<typename T>
    using Slice = Variant<T (&)[]>;
}

#endif //CC_SLICE_H
