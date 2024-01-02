#ifndef RE_NO_IMGUI
#pragma once 
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Raccoon/Scene/Components.h>

namespace Raccoon
{
    enum class GuizmoMode
    {
        Move = 0,
        Rotate, 
        Scale
    };
 
    class Guizmo
    {
    public:
        static void InitWindow(const ImVec2& position, const ImVec2& size);
        static void Manipulate2D(const glm::mat3* viewMatrix, const glm::mat3* projectionMatrix, Transform2DComponent *transform, GuizmoMode mode);
    private:
        static void InitData();

        static ImVec2 WorldToPosition(const glm::vec2 &worldPosition, const glm::mat3 &transform);

        static ImVec2 GetObjectCenterScreenPos();
        static glm::vec2 GetObjectCenterWorldPosition(const glm::vec2 screenPosition);

        static bool HandleUserInput(const ImVec2& objectCenterScreenPos);
        
        static void CalculateColorsAndSizes();

        static void DrawTranslation2D(const ImVec2& objectCenterScreenPos);
        static void DrawRotation2D();
        static void DrawScale2D();

        // static glm::vec2 ConvertPixelsToWorldSpace(const ImVec2& pixelDelta, const glm::mat3& projectionMatrix);
        static glm::vec2 ConvertPixelsToWorldSpace(const ImVec2& pixelCoords);
    };
}
#endif