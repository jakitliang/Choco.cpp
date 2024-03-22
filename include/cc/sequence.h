//
// Created by Jakit on 2024/3/22.
//

#ifndef CHOCO_CPP_SEQUENCE_H
#define CHOCO_CPP_SEQUENCE_H

#include "cc/types.h"

namespace CC {
    template<typename T>
    struct Sequence {
        virtual Size Count() const = 0;

        virtual T & operator[](Size index) = 0;

        virtual const T & operator[](Size index) const = 0;
    };
}

#endif //CHOCO_CPP_SEQUENCE_H
