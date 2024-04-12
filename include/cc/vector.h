//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/17.
//

#ifndef CHOCO_CPP_VECTOR_H
#define CHOCO_CPP_VECTOR_H

#include "cc/list.h"
#include <iterator>

namespace CC {
    template<typename T>
    struct Trivial : IList<T> {
        struct Entity {
            using Type = T [];

            Size Count() const {
                return CC::Count<T>(this);
            }

            T & operator[](Size index) {
                return reinterpret_cast<T *>(this)[index];
            }

            const T & operator[](Size index) const {
                return reinterpret_cast<const T *>(this)[index];
            }

            void Replace(Size index, const T * elements, Size cnt, bool construct = true) {
                if (construct) {
                    CC::CopyConstruct<T>(reinterpret_cast<T *>(this), index, elements, cnt);
                    return;
                }

                CC::Copy<T>(reinterpret_cast<T *>(this), index, elements, cnt);
            }

            void Replace(Size index, T * elements, Size cnt, bool construct = true) {
                if (construct) {
                    CC::MoveConstruct<T>(reinterpret_cast<T *>(this), index, elements, cnt);
                    return;
                }

                CC::Move<T>(reinterpret_cast<T *>(this), index, elements, cnt);
            }

            void Clear(Size index, Size cnt) {
                CC::Destruct<T>(reinterpret_cast<T *>(this), index, cnt);
            }

            // Iterator methods

            T * begin() {
                return reinterpret_cast<T *>(this);
            }

            T * end() {
                return reinterpret_cast<T *>(this) + CC::Count<T>(this);
            }

            // Live cycle methods

            static Entity * Alloc(Size cnt) {
                return reinterpret_cast<Entity *>(CC::Alloc<T>(cnt));
            }

            static Entity * Make(Size cnt) {
                return reinterpret_cast<Entity *>(CC::Make<T>(cnt));
            }

            static Entity * Clone(const Entity * entity) {
                auto ptr = CC::Alloc<T>(entity->Count());
                CC::CopyConstruct(ptr, 0, reinterpret_cast<const T *>(entity), entity->Count());
                return reinterpret_cast<Entity *>(ptr);
            }

            Entity * ReAlloc(Size cnt) {
                return reinterpret_cast<Entity *>(CC::ReMake<T>(this, cnt));
            }

            bool Release() {
                return CC::Destroy(reinterpret_cast<T *>(this));
            }
        };

        Entity * object;
        Size count;

        Trivial() : object(Entity::Make(0)), count(0) {}

        Trivial(const Trivial & vector) : object(Entity::Clone(vector.object)), count(vector.count) {}

        Trivial(Trivial && vector) : object(vector.object), count(vector.count) { vector.object = nullptr; vector.count = 0; }

        explicit Trivial(Size count) : object(Entity::Make(count)), count(0) {}

        ~Trivial() override {
            if (object == nullptr) return;
            object->Release();
            object = nullptr;
            count = 0;
        }

        // Common methods

        template<typename E>
        void Insert(Size index, E * elements, Size cnt) {
            if (cnt < 1) return;

            auto indexEnd = count + cnt;

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
            if (index > count) {
                index = count; // Fix insert position
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

            if (index < count) {
                // Move part 3 to the end
                object->Replace(index + cnt,
                                &(*object)[index],
                                count - index);
            }

            // Insert part 2 into data
            object->Replace(index, elements, cnt);

            count += cnt;
        }

        void CopyInsert(Size index, const T * elements, Size cnt) override {
            Insert(index, elements, cnt);
        }

        void MoveInsert(Size index, T * elements, Size cnt) override {
            Insert(index, elements, cnt);
        }

        T & Last() override {
            if (count == 0) abort();
            return (*object)[count - 1];
        }

        void Delete(Size index, Size cnt) override {
            if (cnt < 1) return;

            if (index >= count) return;

            // Erase
            // Part 1             Part 2              // Part 3
            // data[0 .. index] + erase[0 .. count] + data[index .. last]
            // Part 1                                 // Part 3
            // data[0 .. index]         +             data[index .. last]

            auto indexEnd = index + cnt;

            // Case 1: From index remove to the data.end
            // x: place to remove
            // | | | |x|x|
            if (indexEnd >= count) {
                object->Clear(index, count - index);
                count = index;
                return;
            }

            object->Replace(index, &(*object)[indexEnd], count - indexEnd, false);
            object->Clear(count - cnt, cnt);

            count -= cnt;
        }

        Size Count() const override {
            return count;
        }

        T & operator[](Size index) override {
            if (index >= count) abort();
            return (*object)[index];
        }

        const T & operator[](Size index) const override {
            if (index >= count) abort();
            return (*object)[index];
        }

        // Iterator methods

        struct Iterator {
            using difference_type = T;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::forward_iterator_tag;

            Iterator() : cur(nullptr) {};

            Iterator(const Iterator & iterator) : cur(iterator.cur) {}

            Iterator(Iterator && iterator) noexcept : cur(iterator.cur) { iterator.cur = nullptr; }

            explicit Iterator(T * object) : cur(object) { object = nullptr; }

            Iterator & operator=(const Iterator & iterator) {
                if (this == &iterator) return *this;

                cur = iterator.cur;
                return *this;
            }

            Iterator & operator=(Iterator && iterator) noexcept {
                if (this == &iterator) return *this;

                cur = iterator.cur;

                iterator.cur = nullptr;

                return *this;
            }

            // Incrementing means going through the list
            Iterator & operator++() {
                if (cur == nullptr) return *this;
                cur = ++cur;
                return *this;
            }

            Iterator & operator+(Size index) {
                if (cur == nullptr) return *this;

                for (Size i = 0; i < index; ++i) {
                    cur = ++cur;
                }

                return *this;
            }

            // It needs to be able to compare nodes
            bool operator!=(const Iterator &other) {
                return this->cur != other.cur;
            }

            bool operator==(const Iterator &other) {
                return this->cur == other.cur;
            }

            // Return the data from the node (dereference operator)
            T & operator*() {
                return *this->cur;
            }

            const T & operator*() const {
                return *this->cur;
            }

            template<typename OS>
            friend OS & operator<<(OS & os, const Iterator & iterator) {
                return os << *iterator;
            }

            T * cur;
        };

        Iterator begin() {
            return Iterator(object->begin());
        }

        Iterator end() {
            return Iterator(object->end());
        }
    };

    template<typename T>
    using Vector = List<Trivial<T>>;
}

#endif //CHOCO_CPP_VECTOR_H
