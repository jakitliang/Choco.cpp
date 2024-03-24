//
// Created by Jakit on 2024/3/10.
//

#ifndef CC_OBJECT_H
#define CC_OBJECT_H

#include "zone.h"
#include "variant.h"

namespace CC {
    template<>
    struct Var<void> {
        struct Inspector {
            Byte * Bytes() {
                return reinterpret_cast<Byte *>(this);
            }

            const Byte * Bytes() const {
                return reinterpret_cast<const Byte *>(this);
            }

            Size size() {
                return Zone::Count(this);
            }

            Size size() const {
                return Zone::Count(this);
            }

            Byte & operator[](Size index) {
                return reinterpret_cast<Byte *>(this)[index];
            }

            const Byte & operator[](Size index) const {
                return reinterpret_cast<const Byte *>(this)[index];
            }

            Byte * begin() {
                return reinterpret_cast<Byte *>(this);
            }

            const Byte * begin() const {
                return reinterpret_cast<const Byte *>(this);
            }

            Byte * end() {
                return reinterpret_cast<Byte *>(this) + size();
            }

            const Byte * end() const {
                return reinterpret_cast<const Byte *>(this) + size();
            }
        };

        virtual Inspector & Inspect() {
            return reinterpret_cast<Inspector &>(*this);
        }

        static void * operator new(Size size) {
            return Zone::Alloc(size);
        }

        static void * operator new[](Size size) {
            return Zone::Alloc(size);
        }

        static void * operator new(Size size, void * ptr) {
            if (Zone::Count(ptr) != size) {
                return Zone::ReAlloc(ptr, size);
            }

            return ptr;
        }

        static void * operator new[](Size size, void * ptr) {
            if (Zone::Count(ptr) != size) {
                return Zone::ReAlloc(ptr, size);
            }

            return ptr;
        }

        static void operator delete(void * object) {
            Zone::Release(object);
        }

        static void operator delete[](void * object) {
            Zone::Release(object);
        }
    };

    using Object = Var<void>;
}

#endif //CC_OBJECT_H
