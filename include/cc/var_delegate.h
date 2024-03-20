//
// Created by Jakit on 2024/3/18.
//

#ifndef CHOCO_CPP_VAR_DELEGATE_H
#define CHOCO_CPP_VAR_DELEGATE_H

#include "object.h"
#include "list.h"

namespace CC {
    template<typename T, template<typename> class Base>
    struct Variant<Base<T>> : Variant<void> {
        using Type = Base<T>;
        Type * object;

        Variant() : object(Make<Type>()) {}

        Variant(const Variant & list) : object(Retain(list.object)) {}

        Variant(Variant && list) : object(Retain(list.object)) {
            Destroy(list.object);
            list.object = nullptr;
        }

//        template<Size S>
//        Variant(const T (&array)[S]) : object() {
//            Replace(&object[0], 0, &array[0], S);
//        }
//
//        template<Size S>
//        Variant(T (&&array)[S]) : object(*reinterpret_cast<T (*)[]>(Zone::Alloc<T>(S))){
//            Replace(&object[0], 0, &array[0], S);
//        }

        ~Variant() {
            Destroy(object);
        }
    };
}

#endif //CHOCO_CPP_VAR_DELEGATE_H
