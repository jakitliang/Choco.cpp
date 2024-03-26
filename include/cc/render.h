//
// Created by liangjie on 2024/3/26.
//

#ifndef CHOCO_CPP_RENDER_H
#define CHOCO_CPP_RENDER_H

namespace CC {
    struct Render {
        void * handle;

        Render();

        Render(const Render & render);

        Render(Render && render);

        ~Render();
    };
}

#endif //CHOCO_CPP_RENDER_H
