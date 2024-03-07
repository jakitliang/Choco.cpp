//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#ifndef CC_POINTER_H
#define CC_POINTER_H

#include "cc/numeric.h"
#include "cc/object.h"

namespace CC {
    struct Pointer {
        using Initializer = void (*)(void *);
        using Finalizer = void (*)(void *);

        void * ptr;

        Pointer() = default;

        Pointer(void * const & p);

        Pointer(Object * const & object);

        // Methods

        void * Element(Size index);

        const void * Element(Size index) const;

        Size SizeOfElement() const;

        Size Count() const;

        Size Length() const;

        void ReplaceElements(Size index, const void * elements, Size count);

        // Operators

        Pointer & operator=(void * const & p);

        operator void *();

        operator const void *() const;

        // Static methods for lifecycle

        static void * Alloc(Size size, Size count);

        template<typename T>
        static T * Alloc(Size count) {
            return static_cast<T *>(Alloc(sizeof(T), count));
        }

        static void * Retain(void * object);

        template<typename T>
        static T * Retain(void * object) {
            return static_cast<T *>(Retain(object));
        }

        static void * ReAlloc(void * object, Size count);

        template<typename T>
        static T * ReAlloc(void * object, Size count) {
            return static_cast<T *>(ReAlloc(object, count));
        }

        static bool Release(void * object);

        // Static methods for pointer

        static void * Element(void * object, Size index);

        static const void * Element(const void * object, Size index);

        static Size SizeOfElement(const void * object);

        static Size Count(const void * object);

        static Size Length(const void * object);

        static void ReplaceElements(void * object, Size index, const void * elements, Size count);
    };
}

#endif //CC_POINTER_H
