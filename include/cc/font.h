//
// Created by liangjie on 2024/4/16.
//

#ifndef CHOCO_CPP_FONT_H
#define CHOCO_CPP_FONT_H

#include "cc/types.h"

namespace CC {
    struct Font {
        void * Handle;

        Font();

        Font(const Font & font);

        ~Font();

        bool Open(const char * name, Size size);

        bool Open(const Byte * bytes, Size bytesLength, Size size);

        void Close();

        Font & operator=(const Font & font);
    };
}

#endif //CHOCO_CPP_FONT_H
