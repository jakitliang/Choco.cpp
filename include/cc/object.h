//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/5.
//

#ifndef CC_OBJECT_H
#define CC_OBJECT_H

#include "cc/type.h"
#include "cc/numeric.h"

namespace CC {
    template<>
    struct Type<void> {};

    using Object = Type<void>;
}

#endif //CC_OBJECT_H
