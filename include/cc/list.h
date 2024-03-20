//
// Created by Jakit on 2024/3/21.
//

#ifndef CHOCO_CPP_LIST_H
#define CHOCO_CPP_LIST_H

#include "types.h"

namespace CC {
    template<typename T>
    struct List {
        struct Iterator {
            virtual Iterator begin() = 0;

            virtual Iterator end() = 0;
        };

        virtual void CopyInsert(Size index, const T * elements, Size count) = 0;

        virtual void MoveInsert(Size index, T * elements, Size count) = 0;

        void Insert(Size index, const T & t) {
            CopyInsert(index, &t, 1);
        }

        void Insert(Size index, T && t) {
            MoveInsert(index, &t, 1);
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

        virtual void Delete(Size index, Size count) = 0;

        void Delete(Size index) {
            Delete(index, 1);
        }

        virtual Size Count() const = 0;

        virtual T & operator[](Size index) = 0;

        virtual const T & operator[](Size index) const = 0;

        virtual auto begin() = 0;

        virtual auto end() = 0;
    };
}

#endif //CHOCO_CPP_LIST_H
