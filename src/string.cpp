//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#include "cc/string.h"
#include "cc/zone.h"
#include <cstring>
#include <iostream>

CC::String::String() : Var<char []>(Make<char>(0)), object(*this->delegate), length(Make<Size>()) {}

CC::String::String(const String & str)
    : Var<char []>(str), object(*this->delegate), length(Retain(str.length)) {}

CC::String::String(String && str) noexcept
    : Var<char []>(static_cast<Var &&>(str)), object(*this->delegate), length(str.length) {
    str.length = nullptr;
}

CC::String::String(const char * str, Size length)
    : Var<char []>(Alloc<char>(length)), object(*this->delegate), length(Clone(length)) {
    CopyConstruct<char>(object, 0, str, length);
}

CC::String::String(const char *str)
    : Var<char []>(Alloc<char>(strlen(str))), object(*this->delegate), length(Make<Size>()) {
    *length = strlen(str);
    CopyConstruct<char>(object, 0, str, *length);
}

CC::String::String(const CC::Byte *bytes, CC::Size length)
    : Var<char []>(Alloc<char>(length)), object(*this->delegate), length(Clone(length)) {
    CopyConstruct<char>(object, 0, (const char *) bytes, length);
}

CC::String::~String() {
    Destroy(object);
    Destroy(length);
}

CC::Size CC::String::Length() const {
    return *length;
}

CC::Size CC::String::Count() const {
    return CC::Count<char>(object);
}

char * CC::String::CString() {
    return &object[0];
}

const char * CC::String::CString() const {
    return &object[0];
}

bool CC::String::operator!() const {
    return Length() == 0;
}

void CC::String::Insert(Size index, const char * str, Size len) {
    auto count = Length();
    if (len < 1) return;

    auto indexEnd = count + len;

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

    if (indexEnd > Count()) {
        *this->delegate = ReMake<char>(object, indexEnd);
    }

    // Move the data [index .. Count()] to the end
    // New data           elements[0 .. count]
    // Part 1                                    // Part 3
    // data[0 .. index]                          data[index .. last]
    // Part 1             Part 2                 // Part 3
    // data[0 .. index] + elements[0 .. count] + data[index .. last]

    if (index < count) {
        // Move part 3 to the end
        Copy(object, index + len, &object[index], count - index);
    }

    // Insert part 2 into data
    Copy(object, index, str, len);

    *length += len;
}

void CC::String::Insert(CC::Size index, const char *str) {
    Insert(index, str, strlen(str));
}

void CC::String::Insert(Size index, const char & t) {
    Insert(index, &t, 1);
}

void CC::String::Push(const char * str, Size length) {
    Insert(Length(), str, length);
}

void CC::String::Push(const char * str) {
    Insert(Length(), str, strlen(str));
}

void CC::String::Push(const char & t) {
    Insert(Length(), t);
}

void CC::String::Delete(Size index, Size len) {
    auto count = Length();
    if (len < 1) return;

    if (index >= count) return;

    // Erase
    // Part 1             Part 2              // Part 3
    // data[0 .. index] + erase[0 .. count] + data[index .. last]
    // Part 1                                 // Part 3
    // data[0 .. index]         +             data[index .. last]

    auto indexEnd = index + len;

    // Case 1: From index remove to the data.end
    // x: place to remove
    // | | | |x|x|
    if (indexEnd >= count) {
        Destruct<char>(object, index, count - index);
        *length = index;
        return;
    }

    Move(object, index, &object[indexEnd], count - indexEnd);
    Destruct<char>(object, count - len, len);

    *length -= len;
}

void CC::String::Delete(Size index) {
    Delete(index, 1);
}

char & CC::String::operator[](Size index) {
    if (index >= Length()) {
        std::cerr << "String::[] out of bounds" << std::endl;
        abort();
    }

    return object[index];
}

const char & CC::String::operator[](Size index) const {
    if (index >= Length()) {
        std::cerr << "String::[] out of bounds" << std::endl;
        abort();
    }

    return object[index];
}
