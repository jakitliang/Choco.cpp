//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_STRING_H
#define CC_STRING_H

#include "var.h"
#include "slice.h"

namespace CC {
    template<>
    struct Variant<char (*)[]> {
        using Type = char (**)[];
        using ImmutableType = const char (**)[];

        Type object;
        Size * count;

        Variant();

        Variant(const Variant & arr);

        Variant(Variant && arr) noexcept;

        Variant(const char * str, Size length);

        Variant(const char * str);

        Variant(const Byte * bytes, Size length);

        ~Variant();

        char * begin();

        char * end();

        Size Length() const;

        bool IsEmpty() const;

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

        char * cString();

        const char * cString() const;

        // Static methods for lifecycle

        static Type Alloc() {
            return static_cast<Type>(Pointer::Alloc(sizeof(Type), 1));
        }

        static Type Retain(Type object) {
            return static_cast<Type>(Pointer::Retain(object));
        }

        static Type ReAlloc(Type object, Size count) {
            return static_cast<Type>(Pointer::ReAlloc(object, count));
        }

        static bool Release(Type object) {
            return Pointer::Release(object);
        }
    };

    using String = Variant<char (*)[]>;
}

#endif //CC_STRING_H
