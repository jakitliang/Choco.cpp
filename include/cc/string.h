//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_STRING_H
#define CC_STRING_H

#include "var.h"
#include "slice.h"

namespace CC {
    template<>
    struct Object<char (*)[]> {
        using Class = char (**)[];
        using ImmutableClass = const char (**)[];

        Class object;
        Size * count;

        Object();

        Object(const Object & arr);

        Object(Object && arr) noexcept;

        Object(const char * str, Size length);

        Object(const char * str);

        Object(const Byte * bytes, Size length);

        ~Object();

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

        static Class Alloc() {
            return static_cast<Class>(Pointer::Alloc(sizeof(Class), 1));
        }

        static Class Retain(Class object) {
            return static_cast<Class>(Pointer::Retain(object));
        }

        static Class ReAlloc(Class object, Size count) {
            return static_cast<Class>(Pointer::ReAlloc(object, count));
        }

        static bool Release(Class object) {
            return Pointer::Release(object);
        }
    };

    using String = Object<char (*)[]>;
}

#endif //CC_STRING_H
