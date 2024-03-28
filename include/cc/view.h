//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/28.
//

#ifndef CHOCO_CPP_VIEW_H
#define CHOCO_CPP_VIEW_H

#include "cc/types.h"

namespace CC {
    struct IView {
        virtual void onDraw();

        virtual void onUpdate(Int64 dt);
    };
}

#endif //CHOCO_CPP_VIEW_H
