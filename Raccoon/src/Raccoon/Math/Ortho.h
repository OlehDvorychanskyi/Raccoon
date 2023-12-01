#pragma once
#include <glm/glm.hpp>

namespace Raccoon
{
    glm::mat3 ortho(float left, float right, float bottom, float top) 
    {
        float tx = -(right + left) / (right - left);
        float ty = -(top + bottom) / (top - bottom);

        float a = 2.0f / (right - left);
        float b = 2.0f / (top - bottom);

        return glm::mat3(
            a, 0.0f, tx,
            0.0f, b, ty,
            0.0f, 0.0f, 1.0f
        );
    }
}