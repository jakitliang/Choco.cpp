//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/8.
//

#include "cc/string.h"
#include "cc/zone.h"
#include <cstring>
#include <iostream>

CC::String::String() : Var<char []>(), object(Make<char>(0)), length(Make<Size>()) {
    *delegate = object;
}

CC::String::String(const String & str)
    : Var<char []>(str), object(Retain(str.object)), length(Retain(str.length)) {
    *delegate = object;
}

CC::String::String(String && str) noexcept
    : Var<char []>(static_cast<Var &&>(str)), object(str.object), length(str.length) {
    *delegate = object;
    str.object = nullptr;
    str.length = nullptr;
}

CC::String::String(const char * str, Size length)
    : Var<char []>(), object(Alloc<char>(length)), length(Clone(length)) {
    *delegate = object;
    CopyConstruct<char>(object, 0, str, length);
}

CC::String::String(const char *str)
    : Var<char []>(), object(Alloc<char>(strlen(str))), length(Make<Size>()) {
    *length = strlen(str);
    *delegate = object;
    CopyConstruct<char>(object, 0, str, *length);
}

CC::String::String(const CC::Byte *bytes, CC::Size length)
    : Var<char []>(), object(Alloc<char>(length)), length(Clone(length)) {
    CopyConstruct<char>(object, 0, (const char *) bytes, length);
    *delegate = object;
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
        object = ReMake<char>(object, indexEnd);
        *delegate = object;
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

void CC::String::Push(const char * str, Size len) {
    Insert(Length(), str, len);
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

CC::Var<char []>::Iterator CC::String::end() {
    return Iterator(&object[Length()]);
}

CC::Var<char []>::Iterator CC::String::end() const {
    return Iterator(&object[Length()]);
}

//CC::String::String(const String & str)
//    : Var<char []>(str), object(*this->delegate), length(Retain(str.length)) {}
//
//CC::String::String(String && str) noexcept
//    : Var<char []>(static_cast<Var &&>(str)), object(*this->delegate), length(str.length) {
//    str.length = nullptr;
//}

CC::String &CC::String::operator=(const CC::String &string) {
    if (this == &string) return *this;

    Var<char []>::operator=(string);

    Destroy(object);
    Destroy(length);
    object = Retain(string.object);
    length = Retain(string.length);
    *delegate = object;

    return *this;
}

CC::String &CC::String::operator=(CC::String &&string) noexcept {
    if (this == &string) return *this;

    Var<char []>::operator=(static_cast<String &&>(string));

    Destroy(object);
    Destroy(length);
    object = string.object;
    length = string.length;
    *delegate = object;

    string.object = nullptr;
    string.length = nullptr;

    return *this;
}

bool CC::String::operator==(const char *cString) const {
    return strncmp(object, cString, *length) == 0;
}

bool CC::String::operator==(const CC::String &string) const {
    return strncmp(object, string.object, *length) == 0;
}

bool CC::String::operator!=(const char *cString) const {
    return !operator==(cString);
}

bool CC::String::operator!=(const CC::String &string) const {
    return !operator==(string);
}

CC::String CC::String::operator+(const char *cString) const {
    String tmp(object);
    return tmp.operator+=(cString);
}

CC::String CC::String::operator+(const CC::String &string) const {
    String tmp(object);
    return tmp.operator+=(string.object);
}

CC::String &CC::String::operator+=(const char *cString) {
    Push(cString);

    return *this;
}

CC::String &CC::String::operator+=(const CC::String &string) {
    Push(string.object, *string.length);

    return *this;
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
