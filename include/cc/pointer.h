//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#ifndef CC_POINTER_H
#define CC_POINTER_H

#include "cc/numeric.h"
#include "cc/object.h"

namespace CC {
    template<>
    struct Object<void *> {
        using Class = void *;
        using ImmutableClass = const void *;
        using Initializer = void (*)(Class);
        using Finalizer = void (*)(Class);

        Class object;

        Object() = default;

        template<typename T>
        Object(const Object<T *> & o) {
            object = Retain(o.object);
        }

        ~Object();

        // Methods

        Class Element(Size index);

        ImmutableClass Element(Size index) const;

        Size SizeOfElement() const;

        Size Count() const;

        Size Length() const;

        void ReplaceElements(Size index, ImmutableClass elements, Size count);

        // Operators

        Object & operator=(Class const & p);

        operator void *();

        operator const void *() const;

        // Static methods for lifecycle

        static Class Alloc(Size size, Size count);

        static Class Retain(Class object);

        static Class ReAlloc(Class object, Size count);

        static bool Release(Class object);

        // Static methods for pointer

        static Class Element(Class object, Size index);

        static ImmutableClass Element(ImmutableClass object, Size index);

        static void ReplaceElements(Class object, Size index, ImmutableClass elements, Size count);

        static void BlockCopy(Class object, Size objectIndex, ImmutableClass elements, Size elementsIndex, Size count);

        static Size SizeOfElement(ImmutableClass object);

        static Size Count(ImmutableClass object);

        static Size Length(ImmutableClass object);
    };

    using Pointer = Object<void *>;
}

#endif //CC_POINTER_H
