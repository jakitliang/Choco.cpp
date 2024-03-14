//
// Created by Jakit on 2024/3/14.
//

#ifndef CC_ZONE_H
#define CC_ZONE_H

#include "types.h"
CC_C_BEGIN
#include <malloc.h>
CC_C_END

namespace CC {
    struct Zone {
        struct Record {
            void *End;
            Size Ref;
        };

        static void * Alloc(Size size);

        template<typename T>
        static void * Alloc(Size count) {
            return Alloc(sizeof(T) * count);
        }

        static void * ReAlloc(void * oldObject, Size size);

        static void * Retain(void * object);

        static bool Release(void * object);

        static Size Size(void * object);

        static CC::Size Size(const void * object);

        template<typename T>
        static CC::Size Count(const T * object) {
//            return allocator == nullptr ? 0 : allocator->Count() / sizeof(T);
            return Count(object);
        }
    };
}

#endif //CC_ZONE_H
