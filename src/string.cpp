//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#include "cc/string.h"
#include <cstring>
#include <iostream>

CC::Variant<char (*)[]>::Variant() : object(&Alloc<Type>()) {}

CC::Variant<char (*)[]>::Variant(const Variant & str) : object(&Retain(*str.object)) {}

CC::Variant<char (*)[]>::Variant(Variant && str) noexcept : object(&Retain(*str.object)) {}

CC::Variant<char (*)[]>::Variant(const char * str, Size length) : object(&Alloc<Type>()) {
    object->Insert(0, str, length);
}

CC::Variant<char (*)[]>::Variant(const char *str) : object(&Alloc<Type>()) {
    object->Insert(0, str, strlen(str));
}

CC::Variant<char (*)[]>::Variant(const CC::Byte *bytes, CC::Size length) : object(&Alloc<Type>()) {
    object->Insert(0, reinterpret_cast<const char *>(bytes), length);
}

CC::Variant<char (*)[]>::~Variant() {
    Release(*object);
}

char * CC::Variant<char (*)[]>::begin() {
    return object->begin();
}

char * CC::Variant<char (*)[]>::end() {
    return object->end();
}

CC::Size CC::Variant<char (*)[]>::Length() const {
    return object->Count;
}

char * CC::Variant<char (*)[]>::cString() {
    return &(*object)[0];
}

const char * CC::Variant<char (*)[]>::cString() const {
    return &(*object)[0];
}

char & CC::Variant<char (*)[]>::operator[](Size index) {
    return (*object)[index];
}

const char & CC::Variant<char (*)[]>::operator[](Size index) const {
    return (*object)[index];
}

bool CC::Variant<char (*)[]>::operator!() const {
    return Length() == 0;
}

void CC::Variant<char (*)[]>::Insert(Size index, const char * str, Size length) {
    return object->Insert(index, str, length);
}

void CC::Variant<char (*)[]>::Insert(Size index, const char & t) {
    Insert(index, &t, 1);
}

void CC::Variant<char (*)[]>::Push(const char * str, Size length) {
    Insert(Length(), str, length);
}

void CC::Variant<char (*)[]>::Push(const char * str) {
    Insert(Length(), str, strlen(str));
}

void CC::Variant<char (*)[]>::Push(const char & t) {
    Insert(Length(), t);
}

void CC::Variant<char (*)[]>::Delete(Size index, Size length) {
    object->Delete(index, length);
}

void CC::Variant<char (*)[]>::Delete(Size index) {
    Delete(index, 1);
}
