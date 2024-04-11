//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#ifndef CHOCO_CPP_GRAPHICS_H
#define CHOCO_CPP_GRAPHICS_H

#include "cc/texture.h"
#include "cc/vector2.h"

namespace CC {
    namespace Graphics {
        void Draw(Texture * drawable,
                  Float32 x, Float32 y,
                  Float32 r = 0,
                  Float32 scaleX = 1, Float32 scaleY = 1,
                  Float32 originX = 0, Float32 originY = 0);

        void Line(Float32 startX, Float32 startY, Float32 endX, Float32 endY);

        void Line(const Vector2 & start, const Vector2 & end);

        void SetColor(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha);

        void Clear();

        void Present();
    };
}

#endif //CHOCO_CPP_GRAPHICS_H
