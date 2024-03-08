//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CC_ARRAY_H
#define CC_ARRAY_H

#include "var.h"
#include "slice.h"

namespace CC {
    template<typename T>
    struct Object<T (*)[]> {
        using Class = T (**)[];
        using ImmutableClass = const T (**)[];

        Class object;
        Size * count;

        Object() : object(Alloc()), count(Var<Size>::Alloc(1)) {
            *object = Slice<T>::Alloc(0);
            *count = 0;
        }

        Object(const Object & arr) : object(Retain(arr.object)),
                                     count(Var<Size>::Retain(arr.count)) {}

        Object(Object && arr) : object(Retain(arr.object)),
                                count(Var<Size>::Retain(arr.count)) {}

        ~Object() {
            if (object == nullptr) return;

            auto slice = *object;
            if (Pointer::Release(object)) {
                Pointer::Release(slice);
            }

            Pointer::Release(count);

            object = nullptr;
            count = nullptr;
        }

        T * begin() {
            return &(**object)[0];
        }

        T * end() {
            return &(**object)[Count()];
        }

        Size Count() {
            return *count;
        }

        Size Capacity() {
            return Pointer::Count(*object);
        }

        T & operator[](Size index) {
            return (**object)[index];
        }

        const T & operator[](Size index) const {
            return (**object)[index];
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
                *object = Slice<T>::ReAlloc(*object, indexEnd);
            }

            // Move the data [index .. Count()] to the end
            // New data           elements[0 .. count]
            // Part 1                                    // Part 3
            // data[0 .. index]                          data[index .. last]
            // Part 1             Part 2                 // Part 3
            // data[0 .. index] + elements[0 .. count] + data[index .. last]

            if (index < Count()) {
                // Move part 3 to the end
                Pointer::ReplaceElements(*object,
                                         index + cnt,
                                         Pointer::Element(*object, index),
                                         Count() - index);
            }

            // Insert part 2 into data
            Pointer::ReplaceElements(*object, index, elements, cnt);

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

        void Delete(Size index, Size cnt) {
            if (cnt < 1) return;

            if (index >= Count()) return;

            // Erase
            // Part 1             Part 2              // Part 3
            // data[0 .. index] + erase[0 .. count] + data[index .. last]
            // Part 1                                 // Part 3
            // data[0 .. index]         +             data[index .. last]

            auto indexEnd = index + cnt;

            // Case 1: From index remove to the data.end
            // x: place to remove
            // | | | |x|x|
            if (indexEnd >= Count()) {
                *count = index;
                return;
            }

            Pointer::ReplaceElements(*object, index, Pointer::Element(*object, indexEnd), Count() - indexEnd);

            *count -= cnt;
        }

        void Delete(Size index) {
            Delete(index, 1);
        }

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

    template<typename T>
    using Array = Object<T (*)[]>;
}

#endif //CC_ARRAY_H
