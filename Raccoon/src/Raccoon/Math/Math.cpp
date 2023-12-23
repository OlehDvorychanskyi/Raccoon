#include <Raccoon/Math/Math.h>
#include <Raccoon/Core/Application.h>

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

    float ConvertValue(float value, float fromMin, float fromMax, float toMin, float toMax)
    {
        // value = std::max(std::min(value, fromMax), fromMin);

        float fromRange = fromMax - fromMin;
        float toRange = toMax - toMin;
        float mappedValue = (((value - fromMin) * toRange) / fromRange) + toMin;

        return mappedValue;
    }

    glm::vec2 ConvertToPixels(const glm::mat3 &transform, const glm::vec2 &windowSize)
    {
        glm::vec3 objectClipSpace = transform * glm::vec3(0.0f, 0.0f, 1.0f);

        // Map to screen coordinates
        glm::vec2 objectScreenPos;
        objectScreenPos.x = (objectClipSpace.x + 1.0f) * 0.5f * windowSize.x;
        objectScreenPos.y = (1.0f - objectClipSpace.y) * 0.5f * windowSize.y;

        return objectScreenPos;
    }

    glm::vec2 WorldToScreen(const glm::vec2 &worldPosition, const glm::mat3 &transform, const glm::vec2 &windowSize, const glm::vec2 &windowPosition)
    {
        glm::vec3 objectCenterClipSpace = transform * glm::vec3(worldPosition, 1.0f);

        auto MainWindowWidth = Application::Get().GetWindow().GetWidth();
        auto MainWindowHeight = Application::Get().GetWindow().GetHeight();

        auto ObjectWorldCoordsX = -1.f + (windowSize.x / MainWindowWidth);
        auto ObjectWorldCoordsY = -(windowSize.y / MainWindowHeight) + 1.f;

        auto NewRangeX = ConvertValue(objectCenterClipSpace.x, -1.f, 1.f, -1.f, 0.f);
        auto NewRangeY = ConvertValue(objectCenterClipSpace.y, -1.f, 1.f, 1.f, 0.f);

        glm::vec2 objectCenterScreenPos;
        objectCenterScreenPos.x = ConvertValue(NewRangeX, -1.f, ObjectWorldCoordsX, windowPosition.x, windowPosition.x + windowSize.x);
        objectCenterScreenPos.y = ConvertValue(NewRangeY, ObjectWorldCoordsY, 1.f, windowPosition.y, windowPosition.y + windowSize.y);

        return objectCenterScreenPos;
    }   

    glm::vec2 ScreenToWorld(const glm::vec2 &screenPosition, const glm::mat3 &inverseTransform, const glm::vec2 &windowSize)
    {
        auto MainWindowWidth = Application::Get().GetWindow().GetWidth();
        auto MainWindowHeight = Application::Get().GetWindow().GetHeight();

        glm::vec2 ScreenPosition;
        ScreenPosition.x = (screenPosition.x < 0.f) ? 0.f : ((screenPosition.x <= windowSize.x) ? screenPosition.x : windowSize.x);
        ScreenPosition.y = (screenPosition.y < 0.f) ? 0.f : ((screenPosition.y <= windowSize.y) ? screenPosition.y : windowSize.y);

        float Y = ConvertValue(ScreenPosition.y, 0.f, windowSize.y, windowSize.y, 0.f); 

        glm::vec2 MainWindowUnitPixelValue;
        MainWindowUnitPixelValue.x = 2.f / MainWindowWidth;
        MainWindowUnitPixelValue.y = 2.f / MainWindowHeight;

        glm::vec2 MainWindowClipCoords;
        MainWindowClipCoords.x = (MainWindowUnitPixelValue.x * screenPosition.x) - 1.f; // -1.f to make value in range [-1; 1]
        MainWindowClipCoords.y = (MainWindowUnitPixelValue.y * Y) - 1.f;

        glm::vec3 clipSpace = glm::vec3(MainWindowClipCoords, 1.0f);
        glm::vec3 WorldPosition = inverseTransform * clipSpace;

        return glm::vec2(WorldPosition.x, WorldPosition.y);
    }
}