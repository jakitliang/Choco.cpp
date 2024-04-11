//
// Created by liangjie on 2024/4/1.
//

#ifndef CHOCO_CPP_IMAGE_H
#define CHOCO_CPP_IMAGE_H

#include "cc/texture.h"

namespace CC {
    struct ImageData;
    struct Renderer;

    struct Image : Texture {
        void * Handle;

        Image();

        Image(const Image & image);

        Image(Image && image);

        ~Image() override;

        bool Open(Renderer * renderer, const char * fileName);

        bool Open(Renderer * renderer, const void * buffer, Size size);

        bool Open(Renderer * renderer, ImageData * imageData);

        void Close();

        void * GetHandle() override;

        Image & operator=(const Image & image);

        Image & operator=(Image && image);
    };
}

#endif //CHOCO_CPP_IMAGE_H
