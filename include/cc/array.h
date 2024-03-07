//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CC_ARRAY_H
#define CC_ARRAY_H

#include "cc/var.h"
#include "cc/pointer.h"

namespace CC {
    template<typename T>
    struct Type<T (*)[]> : Object {
        Var<T> * var;
        Size * count;

        Type() : var(Pointer::Alloc<Var<T>>(1)), count(Pointer::Alloc<Size>(1)) {
            var->ptr = Pointer::Alloc<Type<T>>(0);
            *count = 0;
        }

        Type(const Type & arr) : var(Pointer::Retain<Var<T>>(arr.var)),
                                 count(Pointer::Retain<Size>(arr.count)) {}

        Type(Type && arr) : var(Pointer::Retain<Var<T>>(arr.var)),
                            count(Pointer::Retain<Size>(arr.count)) {}

        ~Type() {
            Pointer::Release(var->ptr);
            Pointer::Release(var);
            Pointer::Release(count);
            var = nullptr;
            count = nullptr;
        }

        Value<T> * begin() {
            return &var->ptr[0];
        }

        Value<T> * end() {
            return &var->ptr[Count()];
        }

        Size Count() {
            return *count;
        }

        Size Capacity() {
            return ((Pointer) var->ptr).Count();
        }

        T & operator[](Size index) {
            return var->ptr[index].value;
        }

        const T & operator[](Size index) const {
            return var->ptr[index].value;
        }

        // Algorithms

        void Insert(Size index, const T * elements, Size cnt) {
            if (cnt < 1) return;

            auto indexEnd = Count() + cnt;

            // Case: out of bound
            // 0 1 2 3 4 5
            //         |-|
            // | | | |
            // | | | |0|-:
            // --------------------
            // Aligned to the end
            // 0 1 2 3 4 5
            //       |-|
            // | | | |
            // | | | |-|
            if (index > Count()) {
                index = Count(); // Fix insert position
            }

            if (indexEnd > Capacity()) {
                var->ptr = Pointer::ReAlloc<Type<T>>(var->ptr, indexEnd);
            }

            // Move the data [index .. Count()] to the end
            // New data           elements[0 .. count]
            // Part 1                                    // Part 3
            // data[0 .. index]                          data[index .. last]
            // Part 1             Part 2                 // Part 3
            // data[0 .. index] + elements[0 .. count] + data[index .. last]

            if (index < Count()) {
                // Move part 3 to the end
                Pointer::ReplaceElements(var->ptr,
                                         index + cnt,
                                         Pointer::Element(var->ptr, index),
                                         Count() - index);
            }

            // Insert part 2 into data
            Pointer::ReplaceElements(var->ptr, index, elements, cnt);

            *count += cnt;
        }

        void Insert(Size index, const T & t) {
            Insert(index, &t, 1);
        }

        void Push(const T * elements, Size cnt) {
            Insert(Count(), elements, cnt);
        }

        void Push(const T & t) {
            Insert(Count(), t);
        }

        void Delete(Size index, Size cnt) {}

        void Delete(Size index) {
            if (index >= Count()) return;

            if (index == Count() - 1) {
                *count -=1;
                return;
            }

            Pointer::ReplaceElements(var->ptr,
                                     index,
                                     Pointer::Element(var->ptr, index + 1),
                                     Count() - index - 1);

            *count -= 1;
        }
    };

    template<typename T>
    using Array = Type<T (*)[]>;
}

#endif //CC_ARRAY_H
