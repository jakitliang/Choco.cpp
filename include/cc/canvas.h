//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_CANVAS_H
#define CHOCO_CPP_CANVAS_H

namespace CC {
    struct Canvas {
        void * handle;

        Canvas();

        Canvas(const Canvas & render);

        Canvas(Canvas && render);

        ~Canvas();
    };
}

#endif //CHOCO_CPP_CANVAS_H
