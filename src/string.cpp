//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#include "cc/string.h"
#include <cstring>

CC::Variant<char (*)[]>::Variant() : object(Alloc()), count(Var<Size>::Alloc(1)) {
    *object = Slice<char>::Alloc(0);
    *count = 0;
}

CC::Variant<char (*)[]>::Variant(const Variant & arr) : object(Retain(arr.object)),
                                                        count(Var<Size>::Retain(arr.count)) {}

CC::Variant<char (*)[]>::Variant(Variant && arr) noexcept : object(Retain(arr.object)),
                                                            count(Var<Size>::Retain(arr.count)) {}

CC::Variant<char (*)[]>::Variant(const char * str, Size length) : object(Alloc()),
                                                                  count(Var<Size>::Alloc(1)) {
    *object = Slice<char>::Alloc(length);
    Pointer::ReplaceElements(*object, 0, str, length);
    *count = length;
}

CC::Variant<char (*)[]>::Variant(const char *str) : object(Alloc()),
                                                    count(Var<Size>::Alloc(1)) {
    auto length = strlen(str);
    *object = Slice<char>::Alloc(length);
    Pointer::ReplaceElements(*object, 0, str, length);
    *count = length;
}

CC::Variant<char (*)[]>::Variant(const CC::Byte *bytes, CC::Size length) {
    *object = Slice<char>::Alloc(length);
    Pointer::ReplaceElements(*object, 0, bytes, length);
    *count = length;
}

CC::Variant<char (*)[]>::~Variant() {
    if (object == nullptr) return;

    auto slice = *object;
    if (Pointer::Release(object)) {
        Pointer::Release(slice);
    }

    Pointer::Release(count);

    object = nullptr;
    count = nullptr;
}

char * CC::Variant<char (*)[]>::begin() {
    return &(**object)[0];
}

char * CC::Variant<char (*)[]>::end() {
    return &(**object)[Count()];
}

CC::Size CC::Variant<char (*)[]>::Count() {
    return *count;
}

CC::Size CC::Variant<char (*)[]>::Length() const {
    return *count;
}

bool CC::Variant<char (*)[]>::IsEmpty() const {
    return Length() == 0;
}

CC::Size CC::Variant<char (*)[]>::Capacity() {
    return Pointer::Count(*object);
}

char & CC::Variant<char (*)[]>::operator[](Size index) {
    return (**object)[index];
}

const char & CC::Variant<char (*)[]>::operator[](Size index) const {
    return (**object)[index];
}

void CC::Variant<char (*)[]>::Insert(Size index, const char * str, Size cnt) {
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
        *object = Slice<char>::ReAlloc(*object, indexEnd);
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
    Pointer::ReplaceElements(*object, index, str, cnt);

    *count += cnt;
}

void CC::Variant<char (*)[]>::Insert(Size index, const char & t) {
    Insert(index, &t, 1);
}

void CC::Variant<char (*)[]>::Push(const char * str, Size cnt) {
    Insert(Count(), str, cnt);
}

void CC::Variant<char (*)[]>::Push(const char * str) {
    Insert(Count(), str, strlen(str));
}

void CC::Variant<char (*)[]>::Push(const char & t) {
    Insert(Count(), t);
}

void CC::Variant<char (*)[]>::Delete(Size index, Size cnt) {
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

void CC::Variant<char (*)[]>::Delete(Size index) {
    Delete(index, 1);
}

CC::Size CC::Variant<char (*)[]>::Length(char *str) {
    return strlen(str);
}

char * CC::Variant<char (*)[]>::cString() {
    return reinterpret_cast<char *>(*object);
}

const char * CC::Variant<char (*)[]>::cString() const {
    return reinterpret_cast<const char *>(*object);
}
