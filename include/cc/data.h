//
// Created by liangjie on 2024/3/25.
//

#ifndef CHOCO_CPP_DATA_H
#define CHOCO_CPP_DATA_H

#include "cc/array.h"
#include "cc/zone.h"
#include "cc/sequence.h"

namespace CC {
    struct Data : Var<Byte []> {
        using Type = Byte *;

        Type & object;

        Size * length;

        Data();

        Data(const Data & data);

        Data(Data && data) noexcept;

        Data(const void * bytes, Size length);

        explicit Data(Size length);

        ~Data();

        Size Count() const override;

        Size Length() const;

        // Algorithms

        void Insert(Size index, const Byte * str, Size length);

        void Insert(Size index, const Byte & t);

        void Push(const Byte * str, Size length);

        void Push(const Byte & t);

        void Delete(Size index, Size length);

        void Delete(Size index);

        Byte & operator[](Size index) override;

        const Byte & operator[](Size index) const override;

        template<typename OS>
        friend OS & operator<<(OS & os, const Data & data) {
            char str[4];

            for (int i = 0; i < data.Count(); ++i) {
                os << data.ToHex(str, i) << ' ';
            }
            return os;
        }

        char * ToHex(char (&str)[4], Size index) const;
    };
}

#endif //CHOCO_CPP_DATA_H
