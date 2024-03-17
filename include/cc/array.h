//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CC_ARRAY_H
#define CC_ARRAY_H

#include "collection.h"
#include "var.h"

namespace CC {
    template<typename T>
    struct Variant<T (*)[]> {
        using Type = Collection<T>;
        Type * object;

        Variant() : object(&Alloc<Type>()) {}

        Variant(const Variant & arr) : object(&Retain(*arr.object)) {}

        Variant(Variant && arr) : object(&Retain(*arr.object)) {}

        template<Size S>
        Variant(const T (&array)[S]) : object(){
            Replace(&object[0], 0, &array[0], S);
        }

        template<Size S>
        Variant(T (&&array)[S]) : object(*reinterpret_cast<T (*)[]>(Zone::Alloc<T>(S))){
            Replace(&object[0], 0, &array[0], S);
        }

        ~Variant() {
            Release(*object);
        }

        T * begin() {
            return object->begin();
        }

        T * end() {
            return object->end();
        }

        void Insert(Size index, const T * elements, Size count) {
            object->Insert(index, elements, count);
        }

        void Insert(Size index, const T & t) {
            Insert(index, &t, 1);
        }

        void Push(const T * elements, Size cnt) {
            Insert(Count(), elements, cnt);
        }

        void Push(const T & t) {
            Insert(Count(), t);
        }

        void Delete(Size index, Size count) {
            object->Delete(index, count);
        }

        void Delete(Size index) {
            Delete(index, 1);
        }

        Size Count() const {
            return object->Count;
        }
    };

    template<typename T>
    using Array = Variant<T (*)[]>;
}

#endif //CC_ARRAY_H
