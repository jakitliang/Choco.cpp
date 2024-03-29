//
// Created by Jakit on 2024/3/21.
//

#ifndef CHOCO_CPP_LIST_H
#define CHOCO_CPP_LIST_H

#include "cc/var.h"
#include "cc/sequence.h"

#include <iostream>

using namespace std;

namespace CC {
    template<typename T>
    struct IList : Sequence<T> {
        virtual ~IList() = default;

        virtual void CopyInsert(Size index, const T * elements, Size count) = 0;

        virtual void MoveInsert(Size index, T * elements, Size count) = 0;

        void Insert(Size index, const T & t) {
            CopyInsert(index, &t, 1);
        }

        void Insert(Size index, T && t) {
            MoveInsert(index, &t, 1);
        }

        void Push(const T * elements, Size cnt) {
            Insert(this->Count(), elements, cnt);
        }

        void Push(T * elements, Size cnt) {
            Insert(this->Count(), elements, cnt);
        }

        void Push(const T & t) {
            Insert(this->Count(), t);
        }

        void Push(T && t) {
            Insert(this->Count(), static_cast<T &&>(t));
        }

        virtual void Delete(Size index, Size count) = 0;

        void Delete(Size index) {
            Delete(index, 1);
        }
    };

    template<typename T>
    struct List;

    template<typename T, template<typename> class L>
    struct List<L<T>> : IList<T> {
        using Type = L<T>;
        static_assert(std::is_base_of<IList<T>, Type>::value, "Illegal List type");

        Type * object;

        List() : object(Make<Type>()) {}

        List(const List & list) : object(Retain(list.object)) {}

        List(List && list) : object(list.object) { list.object = nullptr; }

        template<Size S>
        List(const T (&o)[S]) : object(Make<Type>()) {
            object->Push(&o[0], S);
        }

        template<Size S>
        List(T (&&o)[S]) : object(Make<Type>()) {
            object->Push(&o[0], S);
        }

        ~List() override {
            Destroy(object);
        }

        void CopyInsert(Size index, const T * elements, Size count) override {
            object->CopyInsert(index, elements, count);
        }

        void MoveInsert(Size index, T * elements, Size count) override {
            object->MoveInsert(index, elements, count);
        }

        void Delete(Size index, Size count) override {
            object->Delete(index, count);
        }

        Size Count() const override {
            return object->Count();
        }

        List & operator=(const List & list) {
            if (this == &list) return *this;

            Destroy(object);
            object = Retain(list.object);

            return *this;
        }

        List & operator=(List && list) {
            if (this == &list) return *this;

            Destroy(object);
            object = list.object;
            list.object = nullptr;

            return *this;
        }

        T & operator[](Size index) override {
            return object->operator[](index);
        }

        const T & operator[](Size index) const override {
            return object->operator[](index);
        }

        auto begin() {
            return object->begin();
        }

        auto begin() const {
            return object->begin();
        }

        auto end() {
            return object->end();
        }

        auto end() const {
            return object->end();
        }
    };
}

#endif //CHOCO_CPP_LIST_H
