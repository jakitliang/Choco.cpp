//
// Created by liangjie on 2024/4/26.
//

#ifndef JM_DEPLOYER_UI_ELEMENT_H
#define JM_DEPLOYER_UI_ELEMENT_H

#include "cc/bounds.h"
#include "cc/linked_list.h"
#include "cc/vector4.h"
#include <iostream>

namespace CC::UI {
    struct Element {
        Bounds Frame;
        Bounds Bounds;
    };

    bool PointInQuad(const Vector3 & point, const Vector4 & quad);

    bool QuadInQuad(const Vector4 & quad1, const Vector4 & quad2, CC::Vector4 * intersect);

    template<Size S>
    Element * Select(const Vector3 &position, Element * (&elements)[S]) {
        Element * ret = nullptr;
        CC::Float32 max = 0;

        for (int i = 0; i < S; ++i) {
            auto & element = elements[i];
            auto & elementPosition = element->Frame.Position;

            if (PointInQuad(position, {elementPosition.X, elementPosition.Y,
                                       element->Bounds.Size.X, element->Bounds.Size.Y})) {
                if (elementPosition.Z >= max) {
                    max = elementPosition.Z;
                    ret = element;
                    break;
                }
            }
        }

        return ret;
    }
}

#endif //JM_DEPLOYER_UI_ELEMENT_H
