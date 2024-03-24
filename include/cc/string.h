//
// Created by Jakit Liang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_STRING_H
#define CC_STRING_H

#include "cc/variant.h"
#include "cc/sequence.h"

namespace CC {
    template<>
    struct Var<char []> : Sequence<char> {
        using Type = char *;

        Type * object;

        Var();

        Var(const Var & str);

        Var(Var && str) noexcept;

        Var(const char * cStr, Size length);

        Var(const char * cStr);

        Var(const Byte * bytes, Size length);

        ~Var();

        Size Length() const;

        Size Count() const override;

        char * cString();

        const char * cString() const;

        bool operator!() const;

        // Algorithms

        void Insert(Size index, const char * str, Size length);

        void Insert(Size index, const char * str);

        void Insert(Size index, const char & t);

        void Push(const char * str, Size length);

        void Push(const char * str);

        void Push(const char & t);

        void Delete(Size index, Size length);

        void Delete(Size index);

        char & operator[](Size index) override;

        const char & operator[](Size index) const override;

        // Iterator methods

        struct Iterator {
            Iterator() = default;

            // Incrementing means going through the list
            Iterator & operator++();

            Iterator & operator+(Size index);

            // It needs to be able to compare nodes
            bool operator!=(const Iterator &other) const;

            bool operator==(const Iterator &other) const;

            // Return the data from the node (dereference operator)
            char & operator*();

            const char & operator*() const;

            template<typename OS>
            friend OS & operator<<(OS & os, const Iterator & iterator) {
                return os << *iterator;
            }

            char * cur;
        };

        Iterator begin();

        Iterator begin() const;

        Iterator end();

        Iterator end() const;

        template<typename OS>
        friend OS & operator<<(OS &os, const Var & str) {
            return os << str.cString();
        }
    };

    template<Size S>
    struct Var<char [S]> : private Var<char []> {
        using Type = char;

        Var() = delete;

        Var(const Var & var) : Var<char []>(var) {}

        Var(Var && var) : Var<char []>(static_cast<Var &&>(var)) {}

        Var(const char (&o)[S]) : Var<char []>(&o[0], S) {}

        Var(char (&&o)[S]) : Var<char []>(&o[0], S) {}
    };

    using String = Var<char []>;
}

#endif //CC_STRING_H
