//
// Created by Jakit Liang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_STRING_H
#define CC_STRING_H

#include "vector.h"

namespace CC {
    template<>
    struct Variant<char []> {
        using Type = TrivialData<char>;

        Type * object;

        Variant();

        Variant(const Variant & str);

        Variant(Variant && str) noexcept;

        Variant(const char * cStr, Size length);

        Variant(const char * cStr);

        Variant(const Byte * bytes, Size length);

        ~Variant();

        char * begin();

        char * end();

        Size Length() const;

        char * cString();

        const char * cString() const;

        char & operator[](Size index);

        const char & operator[](Size index) const;

        bool operator!() const;

        // Algorithms

        void Insert(Size index, const char * str, Size length);

        void Insert(Size index, const char & t);

        void Push(const char * str, Size length);

        void Push(const char * str);

        void Push(const char & t);

        void Delete(Size index, Size length);

        void Delete(Size index);

        template<typename T>
        friend T & operator<<(T &os, const Variant & str) {
            return os << str.cString();
        }
    };

    using String = Variant<char []>;
}

#endif //CC_STRING_H
