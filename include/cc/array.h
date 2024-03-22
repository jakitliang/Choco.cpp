//
// Created by Jakit Liang<jakitliang@gmail.com> on 2024/3/8.
//

#ifndef CC_ARRAY_H
#define CC_ARRAY_H

#include "cc/var.h"
#include "cc/sequence.h"
#include <iostream>

namespace CC {
    template<typename T>
    struct Variant<T []> : Sequence<T *> {
        using Type = T *;

        T ** object;
        T * objectData;

        Variant() : object(Make<Type>(0)) {}

        Variant(const Variant & var) : object(Retain(var.object)) {}

        Variant(Variant && var) : object(var.object) { var.object = nullptr; }


    };
}

#endif //CC_ARRAY_H
