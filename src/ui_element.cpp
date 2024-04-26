//
// Created by liangjie on 2024/4/26.
//

#include "cc/ui/element.h"

CC::Float32 CC::UI::Element::GetZ() const { return 0; }

CC::Rect CC::UI::Element::Bounds() const { return {0, 0, 0, 0}; }

int CC::UI::Select(const CC::Vector2 & position,
                   const CC::UI::Element * elements, int count,
                   const CC::UI::Element * chosen) {
    CC::Float32 max = 0;

    for (int i = 0; i < count; ++i) {
        if (elements[i].Bounds().Includes(position)) {
            if (elements[i].GetZ() > max) {
                max = elements[i].GetZ();
                chosen = &elements[i];
            }
        }
    }

    return 0;
}
