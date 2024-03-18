//
// Created by Jakit on 2024/3/18.
//

#ifndef CHOCO_CPP_VAR_H
#define CHOCO_CPP_VAR_H

#include "object.h"

namespace CC {
    template<typename T>
    struct Variant {

    };

    template<typename T>
    using Var = Variant<T>;
}

#endif //CHOCO_CPP_VAR_H
