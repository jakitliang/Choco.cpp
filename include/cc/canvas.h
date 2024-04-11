//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_CANVAS_H
#define CHOCO_CPP_CANVAS_H

#include "cc/texture.h"
#include "cc/pixels.h"

namespace CC {
    struct Renderer;

    struct Canvas : Texture {
        void * Handle;

        Canvas();

        Canvas(const Canvas & render);

        Canvas(Canvas && render);

        ~Canvas() override;

        bool Open(Renderer * renderer,
                  Int32 width, Int32 height,
                  UInt32 format = Pixel::Format::RGBA8888);

        void Close();

        void * GetHandle() override;

        Canvas & operator=(const Canvas & canvas);

        Canvas & operator=(Canvas && canvas);
    };
}

#endif //CHOCO_CPP_CANVAS_H
