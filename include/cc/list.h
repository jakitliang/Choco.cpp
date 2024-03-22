//
// Created by Jakit on 2024/3/21.
//

#ifndef CHOCO_CPP_LIST_H
#define CHOCO_CPP_LIST_H

#include "cc/var.h"

#include <iostream>

using namespace std;

namespace CC {
    template<typename T>
    struct IList {
//        virtual ~IList() {};

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
    };

    template<typename T, template<typename> class List>
    struct IList<List<T>> : IList<T> {
        using Type = List<T>;
    };

    template<typename T>
    struct Variant<IList<T>> : IList<T> {
        using Type = IList<T>;

        Type * object;

        Variant() : object(nullptr) {}

        explicit Variant(Type * && o) : object(o) { o = nullptr; }

        ~Variant() override {
            object->~IList();
            Release(object);
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

        T & operator[](Size index) override {
            return object->operator[](index);
        }

        const T & operator[](Size index) const override {
            return object->operator[](index);
        }
    };

    template<typename T, template<typename> class List>
    struct Variant<IList<List<T>>> : IList<T> {
        using Type = typename IList<List<T>>::Type;

        Type * object;

        Variant() : object(Make<Type>()) {}

        Variant(const Variant & var) : object(Retain(var.object)) {}

        Variant(Variant && var) : object(var.object) { var.object = nullptr; }

        ~Variant() {
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

        T & operator[](Size index) override {
            return object->operator[](index);
        }

        const T & operator[](Size index) const override {
            return object->operator[](index);
        }

        auto begin() {
            return object->begin();
        }

        auto end() {
            return object->end();
        }
    };

    template<typename T>
    using List = Variant<IList<T>>;
}

#endif //CHOCO_CPP_LIST_H
