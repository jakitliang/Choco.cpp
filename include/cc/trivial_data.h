//
// Created by Jakit on 2024/3/17.
//

#ifndef CHOCO_CPP_TRIVIAL_DATA_H
#define CHOCO_CPP_TRIVIAL_DATA_H

#include "cc/zone.h"

namespace CC {
    template<typename T>
    struct TrivialData {
        struct Entity {
            using Type = T [];

            Size Count() const {
                return CC::Count<T>(this);
            }

            T & operator[](Size index) {
                return reinterpret_cast<Type &>(*this)[index];
            }

            void Replace(Size index, const T * elements, Size count, bool construct = true) {
                if (construct) {
                    CC::CopyConstruct<T>(reinterpret_cast<T *>(this), index, elements, count);
                    return;
                }

                CC::Copy<T>(reinterpret_cast<T *>(this), index, elements, count);
            }

            void Replace(Size index, T * elements, Size count, bool construct = true) {
                if (construct) {
                    CC::MoveConstruct<T>(reinterpret_cast<T *>(this), index, elements, count);
                    return;
                }

                CC::Move<T>(reinterpret_cast<T *>(this), index, elements, count);
            }

            void Clear(Size index, Size count) {
                CC::Destruct<T>(reinterpret_cast<T *>(this), index, count);
            }

            // Iterator methods

            T * begin() {
                return reinterpret_cast<T *>(this);
            }

            T * end() {
                return reinterpret_cast<T *>(this) + CC::Count<T>(this);
            }

            // Live cycle methods

            static Entity * Alloc(Size count) {
                return reinterpret_cast<Entity *>(Zone::Alloc<T>(count));
            }

            Entity * ReAlloc(Size count) {
                return reinterpret_cast<Entity *>(Zone::ReAlloc<T>(reinterpret_cast<T *>(this), count));
            }

            bool Release() {
                return Zone::Release(this);
            }
        };

        Entity * object;
        Size Count;

        TrivialData() : object(Entity::Alloc(0)), Count(0) {}

        explicit TrivialData(Size count) : object(Entity::Alloc(count)), Count(0) {}

        ~TrivialData() {
            if constexpr (!std::is_trivial<T>::value) {
                for (int i = 0; i < Count; ++i) {
                    (*object)[i].~T();
                }
            }
            object->Release();
        }

        T & operator[](Size index) {
            if (index >= Count) abort();
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

        template<typename E>
        void Insert(Size index, E * elements, Size cnt) {
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
                object->Clear(index, Count - index);
                Count = index;
                return;
            }

            object->Replace(index, &(*object)[indexEnd], Count - indexEnd, false);
            object->Clear(Count - cnt, cnt);

            Count -= cnt;
        }
    };
}

#endif //CHOCO_CPP_TRIVIAL_DATA_H
