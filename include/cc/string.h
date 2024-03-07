//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_STRING_H
#define CC_STRING_H

#include "cc/var.h"
#include "cc/pointer.h"

namespace CC {
    template<>
    struct Type<char (*)[]> : Object {
        Var<char> * var;
        Size * count;

        Type();

        Type(const Type & arr);

        Type(Type && arr) noexcept;

        Type(const char * str, Size length);

        Type(const char * str);

        ~Type();

        Value<char> * begin();

        Value<char> * end();

        Size Count();

        Size Capacity();

        char & operator[](Size index);

        const char & operator[](Size index) const;

        // Algorithms

        void Insert(Size index, const char * str, Size cnt);

        void Insert(Size index, const char & t);

        void Push(const char * str, Size cnt);

        void Push(const char * str);

        void Push(const char & t);

        void Delete(Size index, Size cnt);

        void Delete(Size index);

        static Size Length(char * str);
    };

    using String = Type<char (*)[]>;
}

#endif //CC_STRING_H
