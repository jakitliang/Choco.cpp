//
// Created by JakitLiang<jakitliang@gmail.com> on 2024/3/6.
//

#ifndef CC_OBJECT_H
#define CC_OBJECT_H

namespace CC {
    template<typename T>
    struct Object {
        using Class = T;
    };
}

#endif //CC_OBJECT_H
