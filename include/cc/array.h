//
// Created by Jakit Liang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_ARRAY_H
#define CC_ARRAY_H

#include "cc/var.h"
#include "cc/sequence.h"
#include <bitset>

namespace CC {
    template<typename T>
    struct Variant<T []> : Sequence<T *> {
        using Type = T *;

        Type * object;
        Byte * ref;
        Size * count;

        Variant() : object(Alloc<Type>()), count(Make<Size>()) {
            *object = Make<T>(0);
        }

        Variant(const Variant & var) : object(Retain(var.object)), count(Make<Size>()) {}

        Variant(Variant && var) : object(var.object), count(var.count) {
            var.object = nullptr;
            var.count = nullptr;
        }

        template<Size S>
        Variant(const T (&o)[S]) : object(Alloc<Type>()), count(Make<Size>()) {
            *object = Alloc<T>(S);
            CopyConstruct(*object, 0, &o[0], S);
            *count = S;
        }

        template<Size S>
        Variant(T (&&o)[S]) : object(Alloc<Type>()), count(Make<Size>()) {
            *object = Alloc<T>(S);
            MoveConstruct(*object, 0, &o[0], S);
            *count = S;
        }

        Variant & operator=(const Variant & var) {
            if (this == &var) return *this;

            Destroy(*object);
            Release(object);
            Release(count);

            object = Retain(var.object);
            Retain(*var.object);
            count = Retain(var.count);

            return *this;
        }

        Variant & operator=(Variant && var) {
            if (this == &var) return *this;

            Destroy(*object);
            Release(object);
            Release(count);

            object = var.object;
            count = var.count;
            var.object = nullptr;
            var.count = nullptr;

            return *this;
        }

        template<Size S>
        Variant & operator=(const T (&o)[S]) {
            auto count = Count<T>(*object);

            if (S > count) *object = ReAlloc<T>(S);

            Copy(*object, 0, &o[0], S);

            if (S > count) CopyConstruct(*object, count, &o[count], S - count);

            return *this;
        }

        template<Size S>
        Variant & operator=(T (&&o)[S]) {
            auto count = Count<T>(*object);

            if (S > Count<T>(*object)) *object = ReAlloc<T>(S);

            Move(*object, 0, &o[0], S);

            if (S > count) MoveConstruct(*object, count, &o[count], S - count);

            return *this;
        }

        // Algorithms

        void Insert(Size index, const T * str, Size cnt) {

        }

        void Insert(Size index, T * str, Size cnt);

        void Insert(Size index, const T & t);

        void Insert(Size index, T && t);

        void Push(const T * elements, Size length) {

        }

        void Push(T * elements, Size length);

        void Push(const T & element) {
            Push(element, 1);
        }

        void Push(T && element) {
            Push(element, 1);
        }

        void Delete(Size index, Size cnt);

        void Delete(Size index);

        bool operator!() {
            return *count == 0;
        }

        bool Include(Size index) {
            return
        }
    };
}

#endif //CC_ARRAY_H
