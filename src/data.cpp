//
// Created by liangjie on 2024/3/25.
//

#include "cc/data.h"
#include <iostream>

CC::Data::Data() : Var<Byte []>(Make<Byte>(0)), object(*this->delegate), length(Make<Size>()) {}

CC::Data::Data(const Data & data)
    : Var<Byte []>(data), object(*this->delegate), length(Retain(data.length)) {}

CC::Data::Data(Data && data) noexcept
    : Var<Byte []>(static_cast<Data &&>(data)), object(*this->delegate), length(data.length) {
    data.length = nullptr;
}

CC::Data::Data(const void * bytes, Size length)
    : Var<Byte []>(Alloc<Byte>(length)), object(*this->delegate), length(Clone(length)) {
    CopyConstruct<Byte>(object, 0, reinterpret_cast<const Byte *>(bytes), length);
}

CC::Data::Data(Size length)
    : Var<Byte []>(Alloc<Byte>(length)), object(*this->delegate), length(Clone(length)) {}

CC::Data::~Data() {
    Destroy(object);
    Destroy(length);
}

CC::Size CC::Data::Count() const {
    return CC::Count<Byte>(object);
}

CC::Size CC::Data::Length() const {
    return *length;
}

// Algorithms

void CC::Data::Insert(Size index, const Byte * str, Size len) {
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
        *this->delegate = ReMake<Byte>(object, indexEnd);
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

void CC::Data::Insert(Size index, const Byte & t) {
    Insert(index, &t, 1);
}

void CC::Data::Push(const Byte * str, Size length) {
    Insert(Length(), str, length);
}

void CC::Data::Push(const Byte & t) {
    Insert(Length(), t);
}

void CC::Data::Delete(Size index, Size len) {
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
        Destruct(object, index, count - index);
        *length = index;
        return;
    }

    Move(object, index, &object[indexEnd], count - indexEnd);
    Destruct(object, count - len, len);

    *length -= len;
}

void CC::Data::Delete(Size index) {
    Delete(index, 1);
}

CC::Byte & CC::Data::operator[](Size index) {
    if (index >= Length()) {
        std::cerr << "Data::[] out of bounds" << std::endl;
        abort();
    }

    return object[index];
}

const CC::Byte & CC::Data::operator[](Size index) const {
    if (index >= Length()) {
        std::cerr << "Data::[] out of bounds" << std::endl;
        abort();
    }

    return object[index];
}

char * CC::Data::ToHex(char (&str)[4], CC::Size index) const {
    snprintf(&str[0], 4, "%x", object[index]);
    return str;
}
