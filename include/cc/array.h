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
        using Type = T;

        Type * object;

        Var() : object(nullptr) {}

        Var(const Var & var) : object(Retain(var.object)) {}

        Var(Var && var) : object(var.object) {
            var.object = nullptr;
        }

        Var(T * && object) : object(object) { object = nullptr; }

        ~Var() {
            Destroy(object);
        }

        T & operator[](Size index) {
            return object[index];
        }

        const T & operator[](Size index) const {
            return object[index];
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
            return Iterator(object);
        }

        Iterator begin() const {
            return Iterator(object);
        }

        Iterator end() const {
            return Iterator(object + this->Count());
        }
    };

    template<typename T, Size S>
    struct Var<T [S]> : Var<T []> {
        using Type = T;

        Var() : Var<T []>(Make<Type>(S)) {}

        Var(const Var & var) : Var<T []>(var) {}

        Var(Var && var) : Var<T[]>(static_cast<Var &&>(var)) {}

        Var(const T (&o)[S]) : Var<T[]>(Clone(o)) {}

        Var(T (&&o)[S]) : Var<T[]>(Clone(static_cast<T(&&)[S]>(o))) {}

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
