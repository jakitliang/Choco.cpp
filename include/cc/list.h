//
// Created by Jakit on 2024/3/21.
//

#ifndef CHOCO_CPP_LIST_H
#define CHOCO_CPP_LIST_H

#include "cc/var.h"

namespace CC {
    template<typename T>
    struct IList {
        virtual void CopyInsert(Size index, const T * elements, Size count) = 0;

        virtual void MoveInsert(Size index, T * elements, Size count) = 0;

        virtual void Delete(Size index, Size count) = 0;

        virtual T & operator[](Size index) = 0;

        virtual const T & operator[](Size index) const = 0;
    };

    template<typename T>
    struct Variant<IList<T>> {
        using Type = IList<T>;

        Type * object;

        Variant() : object(nullptr) {}

        Variant(Type * && o) : object(o) { o = nullptr; }

        ~Variant() {
            Release(object);
        }

        void Insert(Size index, const T & t) {
            object->CopyInsert(index, &t, 1);
        }

        void Insert(Size index, T && t) {
            object->MoveInsert(index, &t, 1);
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

        void Delete(Size index) {
            object->Delete(index, 1);
        }

        Size Count() const {
            return object->count();
        }

        T & operator[](Size index) {
            return object->operator[](index);
        }

        virtual const T & operator[](Size index) const {
            return object->operator[](index);
        }

//        auto begin() {
//            return object->begin();
//        };
//
//        auto end() {
//            return object->end();
//        }
    };
}

#endif //CHOCO_CPP_LIST_H
