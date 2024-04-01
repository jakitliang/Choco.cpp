//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_RENDERER_H
#define CHOCO_CPP_RENDERER_H

#include "cc/handle.h"
#include "cc/texture.h"
#include "cc/vector2.h"
#include "cc/rect.h"

namespace CC {
    struct Renderer : Handle {
        ~Renderer() override;

        bool Open(Handle * windowHandle, Int32 index, UInt32 flags);

        void Close();

        // Graphic APIs

        void DrawLine(Float32 startX, Float32 startY, Float32 endX, Float32 endY);

        void DrawLine(const Vector2 & start, const Vector2 & end);

        void DrawLines(const Vector2 (*lines)[], UInt32 count);

        template<Size S>
        void DrawLines(const Vector2 (&lines)[S]) {
            DrawLines(&lines, S);
        }

        void DrawPoint(Float32 positionX, Float32 positionY);

        void DrawPoint(const Vector2 & position);

        void DrawPoints(const Vector2 (*positions)[], UInt32 count);

        template<Size S>
        void DrawPoints(const Vector2 (&positions)[S]) {
            DrawPoints(&positions, S);
        }

        void DrawRect(Float32 x, Float32 y, Float32 width, Float32 height);

        void DrawRect(const Rect & rect);

        void DrawRects(const Rect (*rects)[], UInt32 count);

        template<Size S>
        void DrawRects(const Rect (&rects)[S]) {
            DrawRects(&rects, S);
        }

//        void DrawGeometry();

        void Draw(Handle * textureHandle,
                  Float32 x, Float32 y,
                  Float32 r = 0,
                  Float32 scaleX = 1, Float32 scaleY = 1,
                  Float32 originX = 0, Float32 originY = 0);

        void Draw(Handle * textureHandle,
                  Rect quad,
                  Float32 x, Float32 y,
                  Float32 r = 0,
                  Float32 scaleX = 1, Float32 scaleY = 1,
                  Float32 originX = 0, Float32 originY = 0);

        void Clear();
    };
}

#endif //CHOCO_CPP_RENDERER_H
