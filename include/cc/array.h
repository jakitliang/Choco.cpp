//
// Created by Jakit Liang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_ARRAY_H
#define CC_ARRAY_H

#include "cc/variant.h"
#include "cc/zone.h"
#include "cc/sequence.h"
#include <bitset>

namespace CC {
    template<typename T>
    struct Var<T []> : Sequence<T> {
        using Type = T *;

        Type * delegate;

        Var() : delegate(Make<Type>()) { *delegate = nullptr; }

        Var(const Var & var) : delegate(Retain(var.delegate)) {}

        Var(Var && var) noexcept : delegate(var.delegate) {
            var.delegate = nullptr;
        }

        Var(T * object) : delegate(Make<Type>()) { *delegate = object; }

        ~Var() {
            Destroy(delegate);
        }

        T & operator[](Size index) override {
            return (*delegate)[index];
        }

        const T & operator[](Size index) const override {
            return (*delegate)[index];
        }

        // Iterator methods

        struct Iterator {
            Iterator() : cur(nullptr) {};

            Iterator(const Iterator & iterator) : cur(iterator.cur) {}

            Iterator(Iterator && iterator) noexcept : cur(iterator.cur) {}

            explicit Iterator(T * object) : cur(object) {}

            // Incrementing means going through the list
            Iterator & operator++() {
                if (cur == nullptr) return *this;
                cur = ++cur;
                return *this;
            }

            Iterator & operator+(Size index) {
                if (cur == nullptr) return *this;

                for (Size i = 0; i < index; ++i) {
                    cur = ++cur;
                }

                return *this;
            }

            // It needs to be able to compare nodes
            bool operator!=(const Iterator &other) {
                return this->cur != other.cur;
            }

            bool operator==(const Iterator &other) {
                return this->cur == other.cur;
            }

            // Return the data from the node (dereference operator)
            T & operator*() {
                return *this->cur;
            }

            const T & operator*() const {
                return *this->cur;
            }

            template<typename OS>
            friend OS & operator<<(OS & os, const Iterator & iterator) {
                return os << *iterator;
            }

            T * cur;
        };

        Iterator begin() {
            return Iterator(*delegate);
        }

        Iterator begin() const {
            return Iterator(*delegate);
        }

        virtual Iterator end() {
            return Iterator(*delegate + this->Count());
        }

        virtual Iterator end() const {
            return Iterator(*delegate + this->Count());
        }
    };

    template<typename T, Size S>
    struct Var<T [S]> : Var<T []> {
        using Type = T *;

        Type & object;

        Var() : Var<T []>(Make<T>(S)), object(*this->delegate) {}

        Var(const Var & var) : Var<T []>(var), object(*this->delegate) {}

        Var(Var && var) : Var<T []>(static_cast<Var &&>(var)), object(*this->delegate) {}

        Var(const T (&o)[S]) : Var<T []>(Clone(o)), object(*this->delegate) {}

        Var(T (&&o)[S]) : Var<T []>(Clone(static_cast<T (&&)[S]>(o))), object(*this->delegate) {}

        ~Var() {
            Destroy(object);
        }

        void Resize(Size count) {
            *this->delegate = ReMake<T>(object, count);
        }

        Size Count() const {
            return S;
        }
    };

    template<typename T, Size S>
    Var<T [S]> Array(const T (&object)[S]) {
        return {object};
    }

    template<typename T, Size S>
    Var<T [S]> Array(T (&&object)[S]) {
        return {static_cast<T (&&)[S]>(object)};
    }
}

#endif //CC_ARRAY_H
