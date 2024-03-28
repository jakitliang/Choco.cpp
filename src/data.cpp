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
    : Var<Byte []>(Make<Byte>(length)), object(*this->delegate), length(Make<Size>()) {}

CC::Data::~Data() {
    if (delegate) Destroy(*delegate);
    Destroy(length);
}

void CC::Data::Copy(CC::Size index, const void * buffer, CC::Size len) {
    CC::Copy<Byte>(object, index, static_cast<const Byte *>(buffer), len);
}

void CC::Data::Move(CC::Size index, void * buffer, CC::Size len) {
    CC::Move<Byte>(object, index, static_cast<Byte *>(buffer), len);
}

void CC::Data::Push(const void * buffer, CC::Size len) {
    auto indexEnd = Length() + len;
    if (len < 1) return;

    if (indexEnd > Count()) {
        *this->delegate = ReMake<Byte>(object, indexEnd);
    }

    CC::Copy<Byte>(object, Length(), static_cast<const Byte *>(buffer), len);

    *length += len;
}

void CC::Data::Shift(CC::Size len) {
    auto count = Length();
    if (len < 1) return;

    // Case 1: Remove all
    if (len >= count) {
        *length = 0;
        return;
    }

    CC::Copy(object, 0, &object[len], count - len);

    *length -= len;
}

CC::Size CC::Data::Count() const {
    return CC::Count<Byte>(object);
}

CC::Size & CC::Data::Length() {
    return *length;
}

const CC::Size & CC::Data::Length() const {
    return *length;
}

CC::Byte *CC::Data::CData(CC::Size index) {
    if (index >= Count()) {
        std::cerr << "Data::[] out of bounds" << std::endl;
        abort();
    }

    return &object[index];
}

const CC::Byte *CC::Data::CData(CC::Size index) const {
    if (index >= Count()) {
        std::cerr << "Data::[] out of bounds" << std::endl;
        abort();
    }

    return &object[index];
}

void CC::Data::Resize(CC::Size size) {
    ReMake<Byte>(object, size);
}

CC::Var<CC::Byte[]>::Iterator CC::Data::end() {
    return Iterator(&object[Length()]);
}

CC::Var<CC::Byte[]>::Iterator CC::Data::end() const {
    return Iterator(&object[Length()]);
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

char * CC::Data::ToHex(char (&str)[3], CC::Size index) const {
    snprintf(&str[0], 3, "%x", object[index]);
    return str;
}
