//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_TEXTURE_H
#define CHOCO_CPP_TEXTURE_H

#include "cc/flags.h"
#include "cc/drawable.h"

namespace CC {
    struct Renderer;
    struct ImageData;

    struct Texture : Drawable {
        void * Handle;

        Texture();

        Texture(const Texture & texture);

        Texture(Texture && texture) noexcept;

        ~Texture();

        bool Open(Renderer * renderer,
                  Int32 width, Int32 height,
                  UInt32 format,
                  Int32 access);

        bool Open(Renderer * renderer, ImageData * imageDataHandle);

        void Close();

        Texture & operator=(const Texture & texture);

        Texture & operator=(Texture && texture) noexcept;
    };
}

#endif //CHOCO_CPP_TEXTURE_H
