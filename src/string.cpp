//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#include "cc/string.h"
#include "cc/zone.h"
#include <cstring>

CC::Variant<char []>::Variant() : object(Alloc<Type>()) {
    *object = Make<char>(0);
}

CC::Variant<char []>::Variant(const Variant & str) : object(Retain(str.object)) {}

CC::Variant<char []>::Variant(Variant && str) noexcept : object(str.object) {
    str.object = nullptr;
}

CC::Variant<char []>::Variant(const char * str, Size length) : object(Alloc<Type>()) {
    *object = CopyConstruct<char>(Alloc<char>(length), 0, str, length);
}

CC::Variant<char []>::Variant(const char *str) : object(Alloc<Type>()) {
    auto length = strlen(str);
    *object = CopyConstruct<char>(Alloc<char>(length), 0, str, length);
}

CC::Variant<char []>::Variant(const CC::Byte *bytes, CC::Size length) : object(Alloc<Type>()) {
    *object = CopyConstruct<char>(Alloc<char>(length), 0, (const char *) bytes, length);
}

CC::Variant<char []>::~Variant() {
    Release(*object);
    Release(object);
}

CC::Size CC::Variant<char []>::Length() const {
    return CC::Count<char>(*object);
}

CC::Size CC::Variant<char []>::Count() const {
    return CC::Count<char>(*object);
}

char * CC::Variant<char []>::cString() {
    return &(*object)[0];
}

const char * CC::Variant<char []>::cString() const {
    return &(*object)[0];
}

bool CC::Variant<char []>::operator!() const {
    return Length() == 0;
}

void CC::Variant<char []>::Insert(Size index, const char * str, Size length) {
    auto count = Length();
    if (length < 1) return;

    auto indexEnd = count + length;

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

    if (indexEnd > count) {
        *object = ReMake<char>(*object, indexEnd);
    }

    // Move the data [index .. Count()] to the end
    // New data           elements[0 .. count]
    // Part 1                                    // Part 3
    // data[0 .. index]                          data[index .. last]
    // Part 1             Part 2                 // Part 3
    // data[0 .. index] + elements[0 .. count] + data[index .. last]

    if (index < count) {
        // Move part 3 to the end
        Copy(*object, index + length, &(*object)[index], count - index);
    }

    // Insert part 2 into data
    Copy(*object, index, str, length);
}

void CC::Variant<char[]>::Insert(CC::Size index, const char *str) {
    Insert(index, str, strlen(str));
}

void CC::Variant<char []>::Insert(Size index, const char & t) {
    Insert(index, &t, 1);
}

void CC::Variant<char []>::Push(const char * str, Size length) {
    Insert(Length(), str, length);
}

void CC::Variant<char []>::Push(const char * str) {
    Insert(Length(), str, strlen(str));
}

void CC::Variant<char []>::Push(const char & t) {
    Insert(Length(), t);
}

void CC::Variant<char []>::Delete(Size index, Size length) {
    auto count = Length();
    if (length < 1) return;

    if (index >= count) return;

    // Erase
    // Part 1             Part 2              // Part 3
    // data[0 .. index] + erase[0 .. count] + data[index .. last]
    // Part 1                                 // Part 3
    // data[0 .. index]         +             data[index .. last]

    auto indexEnd = index + length;

    // Case 1: From index remove to the data.end
    // x: place to remove
    // | | | |x|x|
    if (indexEnd >= count) {
        Destruct(*object, index, count - index);
        count = index;
        return;
    }

    Move(*object, index, &(*object)[indexEnd], count - indexEnd);
    Destruct(*object, count - length, length);
}

void CC::Variant<char []>::Delete(Size index) {
    Delete(index, 1);
}

char & CC::Variant<char []>::operator[](Size index) {
    return (*object)[index];
}

const char & CC::Variant<char []>::operator[](Size index) const {
    return (*object)[index];
}

CC::Variant<char[]>::Iterator & CC::Variant<char[]>::Iterator::operator++()  {
    if (cur == nullptr) return *this;
    cur = ++cur;
    return *this;
}

CC::Variant<char[]>::Iterator & CC::Variant<char[]>::Iterator::operator+(CC::Size index) {
    if (cur == nullptr) return *this;

    for (Size i = 0; i < index; ++i) {
        cur = ++cur;
    }

    return *this;
}

bool CC::Variant<char[]>::Iterator::operator!=(const CC::Variant<char[]>::Iterator &other) const {
    return this->cur != other.cur;
}

bool CC::Variant<char[]>::Iterator::operator==(const CC::Variant<char[]>::Iterator &other) const {
    return this->cur == other.cur;
}

char &CC::Variant<char[]>::Iterator::operator*() {
    return *this->cur;
}

const char &CC::Variant<char[]>::Iterator::operator*() const {
    return *this->cur;
}

CC::Variant<char[]>::Iterator CC::Variant<char []>::begin() {
    return {*object};
}

CC::Variant<char[]>::Iterator CC::Variant<char []>::begin() const {
    return {*object};
}

CC::Variant<char[]>::Iterator CC::Variant<char []>::end() {
    return {&(*object)[Length()]};
}

CC::Variant<char[]>::Iterator CC::Variant<char []>::end() const {
    return {&(*object)[Length()]};
}
