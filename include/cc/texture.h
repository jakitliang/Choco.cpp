//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_TEXTURE_H
#define CHOCO_CPP_TEXTURE_H

#include "cc/flags.h"
#include "cc/vector2.h"

namespace CC {
    struct Texture {
//        void * Handle;

//        Texture();
//
//        Texture(const Texture & texture);
//
//        Texture(Texture && texture) noexcept;

        virtual ~Texture() = default;

        // Canvas
//        bool Open(Renderer * renderer,
//                  Int32 width, Int32 height,
//                  UInt32 format,
//                  Int32 access);

//        void Close();

        Float32 GetWidth();

        Float32 GetHeight();

        Vector2 GetSize();

        virtual void * GetHandle() = 0;

//        Texture & operator=(const Texture & texture);
//
//        Texture & operator=(Texture && texture) noexcept;
    };
}

#endif //CHOCO_CPP_TEXTURE_H
