//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/27.
//

#ifndef CHOCO_CPP_GRAPHICS_H
#define CHOCO_CPP_GRAPHICS_H

#include "cc/texture.h"
#include "cc/vector2.h"
#include "cc/vertex.h"

namespace CC::Graphics {
    void Draw(Texture * drawable,
              Float32 x, Float32 y,
              Float32 r = 0,
              Float32 scaleX = 1, Float32 scaleY = 1,
              Float32 originX = 0, Float32 originY = 0);

    void Line(Float32 startX, Float32 startY, Float32 endX, Float32 endY);

    void Line(const Vector2 & start, const Vector2 & end);

    void Line(const CC::Vector2 *lines, CC::UInt32 count);

    template<Size S>
    void Line(const CC::Vector2 (&lines)[S]) {
        Line(&lines[0], S);
    }

    void Geometry2D(Texture * drawable,
                    const Vertex * vertexes, UInt32 count,
                    const UInt32 * indices, UInt32 indicesCount);

    template<Size S1, Size S2>
    void Geometry2D(Texture * drawable,
                    const Vertex (&vertexes)[S1],
                    const UInt32 (&indices)[S2]) {
        Geometry2D(drawable, &vertexes[0], S1, &indices[0], S2);
    }

    void Geometry(Texture * drawable,
                    const Vertex * vertexes, UInt32 count,
                    const UInt32 * indices, UInt32 indicesCount);

    template<Size S1, Size S2>
    void Geometry(Texture * drawable,
                    const Vertex (&vertexes)[S1],
                    const UInt32 (&indices)[S2]) {
        Geometry(drawable, &vertexes[0], S1, &indices[0], S2);
    }

    void SetColor(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha);

//        void SetCanvas()

    void Clear();

    void Present();
}

#endif //CHOCO_CPP_GRAPHICS_H
