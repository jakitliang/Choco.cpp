//
// Created by Jakit on 2024/3/17.
//

#ifndef CHOCO_CPP_COLLECTION_H
#define CHOCO_CPP_COLLECTION_H

#include "cc/data.h"

namespace CC {
    template<typename T>
    struct Collection {
        using Type = Data<T>;

        Type * object;
        Size Count;

        Collection() : object(Type::Alloc(0)), Count(0) {}

        explicit Collection(Size count) : object(Type::Alloc(count)), Count(0) {}

        ~Collection() {
            object->Release();
        }

        T & operator[](Size index) {
            return (*object)[index];
        }

        // Iterator methods

        T * begin() {
            return object->begin();
        }

        T * end() {
            return reinterpret_cast<T *>(object) + Count;
        }

        // Common methods

        void Insert(Size index, const T * elements, Size cnt, bool construct = true) {
            if (cnt < 1) return;

            auto indexEnd = Count + cnt;

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
            if (index > Count) {
                index = Count; // Fix insert position
            }

            if (indexEnd > object->Count()) {
                object = object->ReAlloc(indexEnd);
            }

            // Move the data [index .. Count()] to the end
            // New data           elements[0 .. count]
            // Part 1                                    // Part 3
            // data[0 .. index]                          data[index .. last]
            // Part 1             Part 2                 // Part 3
            // data[0 .. index] + elements[0 .. count] + data[index .. last]

            if (index < Count) {
                // Move part 3 to the end
                object->Replace(index + cnt,
                                &(*object)[index],
                                Count - index);
            }

            // Insert part 2 into data
            object->Replace(index, elements, cnt);

            Count += cnt;
        }

        void Delete(Size index, Size cnt) {
            if (cnt < 1) return;

            if (index >= Count) return;

            // Erase
            // Part 1             Part 2              // Part 3
            // data[0 .. index] + erase[0 .. count] + data[index .. last]
            // Part 1                                 // Part 3
            // data[0 .. index]         +             data[index .. last]

            auto indexEnd = index + cnt;

            // Case 1: From index remove to the data.end
            // x: place to remove
            // | | | |x|x|
            if (indexEnd >= Count) {
                Count = index;
                return;
            }

            object->Replace(index, &(*object)[indexEnd], Count - indexEnd);

            Count -= cnt;
        }
    };
}

#endif //CHOCO_CPP_COLLECTION_H
