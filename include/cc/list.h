//
// Created by Jakit on 2024/3/18.
//

#ifndef CHOCO_CPP_LIST_H
#define CHOCO_CPP_LIST_H

#include "linked_data.h"
#include "object.h"

namespace CC {
    template<typename T>
    struct Variant<T *> : Variant<void> {
        using Type = LinkedData<T>;
        using Iterator = typename LinkedData<T>::Iterator;
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

        void Insert(Size index, const T * elements, Size count) {
            object->Insert(index, elements, count);
        }

        void Insert(Size index, T * elements, Size count) {
            object->Insert(index, elements, count);
        }

        void Insert(Size index, const T & t) {
            Insert(index, &t, 1);
        }

        void Insert(Size index, T && t) {
            Insert(index, &t, 1);
        }

        void Push(const T * elements, Size cnt) {
            Insert(Count(), elements, cnt);
        }

        void Push(T * elements, Size cnt) {
            Insert(Count(), elements, cnt);
        }

        void Push(const T & t) {
            Insert(Count(), t);
        }

        void Push(T && t) {
            Insert(Count(), static_cast<T &&>(t));
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

        T & operator[](Size index) {
            return object->operator[](index);
        }

        const T & operator[](Size index) const {
            return object->operator[](index);
        }

        Iterator begin() {
            return this->object->begin();
        }

        Iterator end() {
            return this->object->end();
        }
    };

    template<typename T>
    using List = Variant<T *>;
}

#endif //CHOCO_CPP_LIST_H
