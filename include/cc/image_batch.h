//
// Created by liangjie on 2024/5/9.
//

#ifndef CHOCO_CPP_IMAGE_BATCH_H
#define CHOCO_CPP_IMAGE_BATCH_H

#include "cc/texture.h"

namespace CC {
    struct ImageData;
    struct Renderer;

    struct ImageBatch : Texture {
        struct Context {
            void * animeHandle;
            UInt32 Frame;
        };

        void * Handle;

        Context * context;

        ImageBatch();

        ImageBatch(const ImageBatch & image);

        ImageBatch(ImageBatch && image);

        ~ImageBatch() override;

        bool Open(const char * fileName);

        bool Open(const void * buffer, Size size);

        bool Open(ImageData * imageData);

        bool Open(Renderer * renderer, const char * fileName);

        bool Open(Renderer * renderer, const void * buffer, Size size);

        bool Open(Renderer * renderer, ImageData * imageData);

        void Close();

        void NextFrame();

        void Render(Int32 x, Int32 y);

        void * GetHandle() override;

        ImageBatch & operator=(const ImageBatch & image);

        ImageBatch & operator=(ImageBatch && image);
    };
}

#endif //CHOCO_CPP_IMAGE_BATCH_H
