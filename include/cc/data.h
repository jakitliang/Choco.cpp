//
// Created by Jakit on 2024/3/19.
//

#ifndef CHOCO_CPP_DATA_H
#define CHOCO_CPP_DATA_H

#include "types.h"

namespace CC {
    template<typename T>
    struct Data {
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
    };
}

#endif //CHOCO_CPP_DATA_H
