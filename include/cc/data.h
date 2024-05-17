//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/25.
//

#ifndef CHOCO_CPP_DATA_H
#define CHOCO_CPP_DATA_H

#include "cc/array.h"
#include "cc/zone.h"
#include "cc/sequence.h"

namespace CC {
    struct Data : Var<Byte []> {
        using Type = Byte;

        Type * object;

        Size * length;

        Data();

        Data(const Data & data);

        Data(Data && data) noexcept;

        Data(const void * bytes, Size length);

        explicit Data(Size length);

        ~Data();

        void Copy(Size index, const void * buffer, Size length);

        void Move(Size index, void * buffer, Size length);

        void Push(const void * buffer, Size length);

        void Shift(Size length);

        template<typename T>
        void Shift(Size count) {
            Shift(sizeof(T) * count);
        }

        Size Count() const override;

        Size & Length();

        const Size & Length() const;

        template<typename T>
        Size Length() {
            return Length() / sizeof(T);
        }

        template<typename T>
        Size Length() const {
            return Length() / sizeof(T);
        }

        Byte * CData(Size index = 0);

        const Byte * CData(Size index = 0) const;

        template<typename T>
        T * CData(Size index = 0) {
            if (index * sizeof(T) > Length()) return nullptr;
            return reinterpret_cast<T *>(CData()) + index;
        }

        template<typename T>
        const T * CData(Size index = 0) const {
            if (index * sizeof(T) > Length()) return nullptr;
            return reinterpret_cast<const T *>(CData()) + index;
        }

        void Resize(Size size);

        void ResizeBy(Int64 size);

        void ResizeByNeeds(Int64 size);

        Byte & operator[](Size index) override;

        const Byte & operator[](Size index) const override;

        Iterator end() override;

        Iterator end() const override;

        template<typename OS>
        friend OS & operator<<(OS & os, const Data & data) {
            char str[3];

            for (int i = 0; i < data.Count(); ++i) {
                os << data.ToHex(str, i) << ' ';
            }
            return os;
        }

        char * ToHex(char (&str)[3], Size index) const;
    };
}

#endif //CHOCO_CPP_DATA_H
