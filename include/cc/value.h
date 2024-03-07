//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/7.
//

#ifndef CC_VALUE_H
#define CC_VALUE_H

#include "cc/object.h"

namespace CC {
    template<typename T>
    struct Type : Object {
        T value;

        Type() = default;

        Type(const T & v) : value(v) {}

        Type & operator=(const T & v) { value = v; }

        T & operator *() { return value; }

        operator T &() { return value; }

        operator T &() const { return value; }
    };

    template<typename T>
    using Value = Type<T>;
}

#endif //CC_VALUE_H
