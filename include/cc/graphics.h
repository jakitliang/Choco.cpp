//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#ifndef CHOCO_CPP_GRAPHICS_H
#define CHOCO_CPP_GRAPHICS_H

#include "cc/image.h"
#include "cc/vector2.h"

namespace CC {
    namespace Graphics {
        void Draw(Image * drawable,
                  Int32 x,
                  Int32 y,
                  Int32 radians,
                  Int32 scaleX,
                  Int32 scaleY,
                  Int32 offsetX,
                  Int32 offsetY);

        void Line(Float32 startX, Float32 startY, Float32 endX, Float32 endY);

        void Line(const Vector2 & start, const Vector2 & end);

        void SetColor(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha);

        void Clear();

        void Present();
    };
}

#endif //CHOCO_CPP_GRAPHICS_H
