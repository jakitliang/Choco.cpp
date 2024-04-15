//
// Created by liangjie on 2024/4/15.
//

#ifndef CHOCO_CPP_BEZIER_PATH_H
#define CHOCO_CPP_BEZIER_PATH_H

#include "cc/vector2.h"

namespace CC {
    struct BezierCurve {
        Vector2 p0;
        Vector2 p1;
        Vector2 p2;
        Vector2 p3;

        Vector2 CalculateCurvePoint(float t) {
            float tt = t * t;
            float ttt = tt * t;
            float u = 1.0f - t;
            float uu = u * u;
            float uuu = uu * u;

            Vector2 point = (uuu * p0) + (3 * uu * t * p1) + (3 * u * tt * p2) + (ttt * p3);
            point.x = round(point.x);
            point.y = round(point.y);

            return point;
        }
    };
}

#endif //CHOCO_CPP_BEZIER_PATH_H
