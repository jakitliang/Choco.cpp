//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#include "cc/string.h"
#include <cstring>

CC::Object<char (*)[]>::Object() : object(Alloc()), count(Var<Size>::Alloc(1)) {
    *object = Slice<char>::Alloc(0);
    *count = 0;
}

CC::Object<char (*)[]>::Object(const Object & arr) : object(Retain(arr.object)),
                                                     count(Var<Size>::Retain(arr.count)) {}

CC::Object<char (*)[]>::Object(Object && arr) noexcept : object(Retain(arr.object)),
                                                         count(Var<Size>::Retain(arr.count)) {}

CC::Object<char (*)[]>::Object(const char * str, Size length) : object(Alloc()),
                                                                count(Var<Size>::Alloc(1)) {
    *object = Slice<char>::Alloc(length);
    Pointer::ReplaceElements(*object, 0, str, length);
    *count = length;
}

CC::Object<char (*)[]>::Object(const char *str) : object(Alloc()),
                                                  count(Var<Size>::Alloc(1)) {
    auto length = strlen(str);
    *object = Slice<char>::Alloc(length);
    Pointer::ReplaceElements(*object, 0, str, length);
    *count = length;
}

CC::Object<char (*)[]>::Object(const CC::Byte *bytes, CC::Size length) {
    *object = Slice<char>::Alloc(length);
    Pointer::ReplaceElements(*object, 0, bytes, length);
    *count = length;
}

CC::Object<char (*)[]>::~Object() {
    if (object == nullptr) return;

    auto slice = *object;
    if (Pointer::Release(object)) {
        Pointer::Release(slice);
    }

    Pointer::Release(count);

    object = nullptr;
    count = nullptr;
}

char * CC::Object<char (*)[]>::begin() {
    return &(**object)[0];
}

char * CC::Object<char (*)[]>::end() {
    return &(**object)[Count()];
}

CC::Size CC::Object<char (*)[]>::Count() {
    return *count;
}

CC::Size CC::Object<char (*)[]>::Length() const {
    return *count;
}

bool CC::Object<char (*)[]>::IsEmpty() const {
    return Length() == 0;
}

CC::Size CC::Object<char (*)[]>::Capacity() {
    return Pointer::Count(*object);
}

char & CC::Object<char (*)[]>::operator[](Size index) {
    return (**object)[index];
}

const char & CC::Object<char (*)[]>::operator[](Size index) const {
    return (**object)[index];
}

void CC::Object<char (*)[]>::Insert(Size index, const char * str, Size cnt) {
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

void CC::Object<char (*)[]>::Insert(Size index, const char & t) {
    Insert(index, &t, 1);
}

void CC::Object<char (*)[]>::Push(const char * str, Size cnt) {
    Insert(Count(), str, cnt);
}

void CC::Object<char (*)[]>::Push(const char * str) {
    Insert(Count(), str, strlen(str));
}

void CC::Object<char (*)[]>::Push(const char & t) {
    Insert(Count(), t);
}

void CC::Object<char (*)[]>::Delete(Size index, Size cnt) {
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

void CC::Object<char (*)[]>::Delete(Size index) {
    Delete(index, 1);
}

CC::Size CC::Object<char (*)[]>::Length(char *str) {
    return strlen(str);
}

char * CC::Object<char (*)[]>::cString() {
    return reinterpret_cast<char *>(*object);
}

const char * CC::Object<char (*)[]>::cString() const {
    return reinterpret_cast<const char *>(*object);
}
