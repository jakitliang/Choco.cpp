//
// Created by liangjie on 2024/3/26.
//

#ifndef CHOCO_CPP_TEXTURE_H
#define CHOCO_CPP_TEXTURE_H


namespace CC {
    struct TextureHandle {
        void * texture;
    };

    struct Texture {
        Texture();

        ~Texture();
    };
}

#endif //CHOCO_CPP_TEXTURE_H
