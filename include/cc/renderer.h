//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_RENDERER_H
#define CHOCO_CPP_RENDERER_H

#include "cc/vector2.h"
#include "cc/rect.h"
#include "cc/vertex.h"

namespace CC {
    struct Window;
    struct Texture;

    struct Renderer {
        struct Context;

        void * Handle;

        Renderer();

        Renderer(const Renderer & renderer) = delete;

        Renderer(Renderer && renderer) noexcept;

        ~Renderer();

        void Close();

        Renderer & operator=(const Renderer & renderer) = delete;

        Renderer & operator=(Renderer && renderer) noexcept;

        // Graphic APIs

        void DrawLine(Float32 startX, Float32 startY, Float32 endX, Float32 endY);

        void DrawLine(const Vector2 & start, const Vector2 & end);

        void DrawLines(const Vector2 *lines, UInt32 count);

        template<Size S>
        void DrawLines(const Vector2 (&lines)[S]) {
            DrawLines(&lines[0], S);
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

        void Draw(void * textureHandle,
                  Float32 x, Float32 y,
                  Float32 r = 0,
                  Float32 scaleX = 1, Float32 scaleY = 1,
                  Float32 originX = 0, Float32 originY = 0);

        void Draw(void * textureHandle,
                  Rect quad,
                  Float32 x, Float32 y,
                  Float32 r = 0,
                  Float32 scaleX = 1, Float32 scaleY = 1,
                  Float32 originX = 0, Float32 originY = 0);

        void DrawGeometry2D(Texture * texture,
                            const Vertex * vertexes, UInt32 count,
                            const UInt32 * indices, UInt32 indicesCount);

        void DrawGeometry3D(Texture * texture,
                            const Vertex * vertexes, UInt32 count,
                            const UInt32 * indices, UInt32 indicesCount);

        void SetColor(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha);

        /**
         * Set Rendering target texture
         * @param texture Texture or passing nullptr will render to window context.
         */
        void SetTarget(Texture * texture);

        void Clear();

        void Present();

        static Renderer * Open(void * windowHandle, Int32 index, UInt32 flags);

        static Renderer * GetCurrent();

        static Renderer * GetWithWindow(Window * window);
    };
}

#endif //CHOCO_CPP_RENDERER_H
