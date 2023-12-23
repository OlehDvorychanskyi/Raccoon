#pragma once
#include <glm/glm.hpp>

namespace Raccoon
{
    glm::mat3 ortho(float left, float right, float bottom, float top);

    float ConvertValue(float value, float fromMin, float fromMax, float toMin, float toMax);
    glm::vec2 ConvertToPixels(const glm::mat3 &transform, const glm::vec2 &windowSize);

    glm::vec2 WorldToScreen(const glm::vec2 &worldPosition, const glm::mat3 &transform, const glm::vec2 &windowSize, const glm::vec2 &windowPosition);
    glm::vec2 ScreenToWorld(const glm::vec2 &screenPosition, const glm::mat3 &inverseTransform, const glm::vec2 &windowSize);
}