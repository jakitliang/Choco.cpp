//
// Created by Jakit on 2024/3/10.
//

#ifndef CC_OBJECT_H
#define CC_OBJECT_H

namespace CC {
    template<typename T>
    struct Variant;

    template<>
    struct Variant<void> {};

    using Object = Variant<void>;
}

#endif //CC_OBJECT_H
