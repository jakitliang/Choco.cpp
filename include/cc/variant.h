//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/6.
//

#ifndef CC_VARIANT_H
#define CC_VARIANT_H

#include "cc/object.h"

namespace CC {
//    template<typename T>
//    struct Variant;
//
//    template<>
//    struct Variant<void> {
//        template<typename T>
//        static T Type(const T & object) {
//            return {};
//        }
//    };

    template<typename T>
    struct Variant : Variant<void> {
//        using Type = T;
//        using ImmutableType = const T;

        static Variant<T> Class(const T & object) {
            return {};
        }
    };
}

#endif //CC_VARIANT_H
