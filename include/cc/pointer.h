//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#ifndef CC_POINTER_H
#define CC_POINTER_H

#include "cc/types.h"
#include "cc/variant.h"

namespace CC {
    template<>
    struct Variant<void *> {
        using Type = void *;
        using ImmutableType = const void *;
        using Initializer = void (*)(Type);
        using Finalizer = void (*)(Type);

        Type object;

        Variant() = default;

        template<typename T>
        Variant(const Variant<T *> & o) {
            object = Retain(o.object);
        }

        ~Variant();

        // Methods

        Type Element(Size index);

        ImmutableType Element(Size index) const;

        Size SizeOfElement() const;

        Size Count() const;

        Size Length() const;

        void ReplaceElements(Size index, ImmutableType elements, Size count);

        // Operators

        Variant & operator=(Type const & p);

        operator void *();

        operator const void *() const;

        // Static methods for lifecycle

        static Type Alloc(Size size, Size count);

        static Type Retain(Type object);

        static Type ReAlloc(Type object, Size count);

        static bool Release(Type object);

        static Type operator new(Size size);

        // Static methods for pointer

        static Type Element(Type object, Size index);

        static ImmutableType Element(ImmutableType object, Size index);

        static void ReplaceElements(Type object, Size index, ImmutableType elements, Size count);

        static void BlockCopy(Type object, Size objectIndex, ImmutableType elements, Size elementsIndex, Size count);

        static Size SizeOfElement(ImmutableType object);

        static Size Count(ImmutableType object);

        static Size Length(ImmutableType object);
    };

    using Pointer = Variant<void *>;
}

#endif //CC_POINTER_H
