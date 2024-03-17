//
// Created by Jakit on 2024/3/17.
//

#ifndef CHOCO_CPP_DATA_H
#define CHOCO_CPP_DATA_H

#include "cc/zone.h"

namespace CC {
    template<typename T>
    struct Data {
        using Type = T [];

        Size Count() const {
            return CC::Count<T>(this);
        }

        T & operator[](Size index) {
            return reinterpret_cast<Type &>(*this)[index];
        }

        void Replace(Size index, const T * elements, Size count) {
            CC::Replace<T>(reinterpret_cast<T *>(this), index, elements, count);
        }

        // Iterator methods

        T * begin() {
            return reinterpret_cast<T *>(this);
        }

        T * end() {
            return reinterpret_cast<T *>(this) + CC::Count<T>(this);
        }

        // Live cycle methods

        static Data * Alloc(Size count) {
            return reinterpret_cast<Data *>(Zone::Alloc<T>(count));
        }

        Data * ReAlloc(Size count) {
            return reinterpret_cast<Data *>(Zone::ReAlloc<T>(reinterpret_cast<T *>(this), count));
        }

        Data * Retain() {
            return reinterpret_cast<Data *>(Zone::Retain(this));
        }

        bool Release() {
            return Zone::Release(this);
        }
    };
}

#endif //CHOCO_CPP_DATA_H
