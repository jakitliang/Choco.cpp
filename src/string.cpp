//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/8.
//

#include "cc/string.h"
#include <cstring>

CC::Type<char (*)[]>::Type() : var(Pointer::Alloc<Var<char>>(1)), count(Pointer::Alloc<Size>(1)) {
    var->ptr = Pointer::Alloc<Type<char>>(0);
    *count = 0;
}

CC::Type<char (*)[]>::Type(const Type & arr) : var(Pointer::Retain<Var<char>>(arr.var)),
                                               count(Pointer::Retain<Size>(arr.count)) {}

CC::Type<char (*)[]>::Type(Type && arr) : var(Pointer::Retain<Var<char>>(arr.var)),
                                count(Pointer::Retain<Size>(arr.count)) {}

CC::Type<char (*)[]>::Type(const char * str, Size length) : var(Pointer::Alloc<Var<char>>(1)),
                                                  count(Pointer::Alloc<Size>(1)) {
    var->ptr = Pointer::Alloc<Type<char>>(length);
    Pointer::ReplaceElements(var->ptr, 0, str, length);
    *count = length;
}

CC::Type<char (*)[]>::Type(const char *str) : var(Pointer::Alloc<Var<char>>(1)),
                                              count(Pointer::Alloc<Size>(1)) {
    auto length = strlen(str);
    var->ptr = Pointer::Alloc<Type<char>>(length);
    Pointer::ReplaceElements(var->ptr, 0, str, length);
    *count = length;
}

CC::Type<char (*)[]>::~Type() {
    Pointer::Release(var->ptr);
    Pointer::Release(var);
    Pointer::Release(count);
    var = nullptr;
    count = nullptr;
}

CC::Value<char> * CC::Type<char (*)[]>::begin() {
    return &var->ptr[0];
}

CC::Value<char> * CC::Type<char (*)[]>::end() {
    return &var->ptr[Count()];
}

CC::Size CC::Type<char (*)[]>::Count() {
    return *count;
}

CC::Size CC::Type<char (*)[]>::Capacity() {
    return ((Pointer) var->ptr).Count();
}

char & CC::Type<char (*)[]>::operator[](Size index) {
    return var->ptr[index].value;
}

const char & CC::Type<char (*)[]>::operator[](Size index) const {
    return var->ptr[index].value;
}

void CC::Type<char (*)[]>::Insert(Size index, const char * str, Size cnt) {
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
        var->ptr = Pointer::ReAlloc<Type<char>>(var->ptr, indexEnd);
    }

    // Move the data [index .. Count()] to the end
    // New data           elements[0 .. count]
    // Part 1                                    // Part 3
    // data[0 .. index]                          data[index .. last]
    // Part 1             Part 2                 // Part 3
    // data[0 .. index] + elements[0 .. count] + data[index .. last]

    if (index < Count()) {
        // Move part 3 to the end
        Pointer::ReplaceElements(var->ptr,
                                 index + cnt,
                                 Pointer::Element(var->ptr, index),
                                 Count() - index);
    }

    // Insert part 2 into data
    Pointer::ReplaceElements(var->ptr, index, str, cnt);

    *count += cnt;
}

void CC::Type<char (*)[]>::Insert(Size index, const char & t) {
    Insert(index, &t, 1);
}

void CC::Type<char (*)[]>::Push(const char * str, Size cnt) {
    Insert(Count(), str, cnt);
}

void CC::Type<char (*)[]>::Push(const char * str) {
    Insert(Count(), str, strlen(str));
}

void CC::Type<char (*)[]>::Push(const char & t) {
    Insert(Count(), t);
}

void CC::Type<char (*)[]>::Delete(Size index, Size cnt) {}

void CC::Type<char (*)[]>::Delete(Size index) {
    if (index >= Count()) return;

    if (index == Count() - 1) {
        *count -=1;
        return;
    }

    Pointer::ReplaceElements(var->ptr,
                             index,
                             Pointer::Element(var->ptr, index + 1),
                             Count() - index - 1);

    *count -= 1;
}

CC::Size CC::Type<char (*)[]>::Length(char *str) {
    return strlen(str);
}
