//
// Created by liangjie on 2024/4/26.
//

#ifndef JM_DEPLOYER_UI_ELEMENT_H
#define JM_DEPLOYER_UI_ELEMENT_H

#include "cc/rect.h"

namespace CC::UI {
    struct Element {
        virtual Rect Bounds() const;

        virtual Float32 GetZ() const;
    };

    static int Select(const Vector2 & position,
                      Element * elements, int count,
                      Element * chosen);

    static int Select(const Vector2 & position,
                      const Element * elements, int count,
                      const Element * chosen);

    template<Size S>
    static int Select(const CC::Vector2 & position, const Element * chosen, const Element (&elements)[S]) {
        return Select(position, &elements[0], S, chosen);
    }

    template<Size S>
    static int Select(const CC::Vector2 & position, Element * chosen, Element (&elements)[S]) {
        return Select(position, &elements[0], S, chosen);
    }
}

#endif //JM_DEPLOYER_UI_ELEMENT_H
