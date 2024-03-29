//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_TEXTURE_H
#define CHOCO_CPP_TEXTURE_H

#include "cc/handle.h"
#include "cc/linked_list.h"

namespace CC {
    struct Texture : Handle {
        ~Texture() override;

        bool Open(Handle * rendererHandle,
                  Int32 width, Int32 height,
                  UInt32 format,
                  Int32 access);

        void Close();
    };
}

#endif //CHOCO_CPP_TEXTURE_H
