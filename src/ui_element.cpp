//
// Created by liangjie on 2024/4/26.
//

#include "cc/ui/element.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"
#include "SDL2/SDL.h"
#include <iostream>

bool CC::UI::PointInQuad(const CC::Vector3 &point, const CC::Vector4 &quad) {
    SDL_FPoint p{point.X, point.Y};
    SDL_FRect r{quad.X, quad.Y, quad.Width, quad.Height};

    return SDL_PointInFRect(&p, &r) == SDL_TRUE;
}

bool CC::UI::QuadInQuad(const CC::Vector4 &quad1, const CC::Vector4 &quad2, CC::Vector4 * intersect) {
    SDL_FRect rect1{quad1.X, quad1.Y, quad1.Width, quad1.Height};
    SDL_FRect rect2{quad2.X, quad2.Y, quad2.Width, quad2.Height};
    SDL_FRect rect3{};

    bool ret = SDL_IntersectFRect(&rect1, &rect2, &rect3) == SDL_TRUE;

    if (ret && intersect != nullptr) *intersect = {rect3.x, rect3.y, rect3.w, rect3.h};

    return ret;
}
