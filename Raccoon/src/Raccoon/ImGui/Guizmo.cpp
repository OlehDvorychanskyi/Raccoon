#include <Raccoon/ImGui/Guizmo.h>
#include <Raccoon/Math/Math.h>
#include <Raccoon/Core/Logger.h>
#include <Raccoon/Core/Application.h>
#include <Raccoon/Core/Input.h>

#include <glm/gtx/matrix_transform_2d.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Raccoon
{
    struct GuizmoData
    {
        ImVec4 WindowRectangle;

        Transform2DComponent* Transform2D = nullptr;
        const glm::mat3 *Projection = nullptr, *View = nullptr;
        glm::mat3 MVP, InverseMVP, ViewProjection, InverseViewProjection;

        // Positions 
        ImVec2 ScreenCenter;

        // InputHandle
        bool IsDragging = false;
        bool IsMovingX = false;
        bool IsMovingY = false;

        bool IsCenterPointHovered = false;
        bool IsXAxisHovered = false;
        bool IsYAxisHovered = false;

        // Sizes
        float CircleRadius = 10.f;

        // Colors

        // Mode 
        GuizmoMode Mode; 
    };  
    static GuizmoData s_Data;

    void Guizmo::InitWindow(const ImVec2& position, const ImVec2& size)
    {
        s_Data.WindowRectangle = {position.x, position.y, size.x, size.y};
    }

    void Guizmo::InitData()
    {
        s_Data.ViewProjection = *(s_Data.Projection) * *(s_Data.View);
        // s_Data.MVP = s_Data.Transform2D->GetTransform() * s_Data.ViewProjection;
        s_Data.MVP = *(s_Data.Projection) * *(s_Data.View) * s_Data.Transform2D->GetTransform(); 
        s_Data.InverseMVP = glm::inverse(s_Data.MVP);
        s_Data.InverseViewProjection = glm::inverse(s_Data.ViewProjection);

        auto center = WorldToScreen({0.f, 0.f}, s_Data.MVP, {s_Data.WindowRectangle.z, s_Data.WindowRectangle.w}, {s_Data.WindowRectangle.x, s_Data.WindowRectangle.y});
        s_Data.ScreenCenter = ImVec2(center.x, center.y);
        // s_Data.ScreenCenter = ConvertWorldToScreenPoint(0.f, 0.f, s_Data.WindowRectangle.z, s_Data.WindowRectangle.w, *s_Data.Projection);
        // s_Data.ScreenCenter = WorldToScreen2D({0.f, 0.f}, s_Data.MVP, s_Data.WindowRectangle.z, s_Data.WindowRectangle.w);

    }

    static void HandleInput()
    {
        switch (s_Data.Mode)
        {
            case GuizmoMode::Move:
            {
                break;
            }
            case GuizmoMode::Rotate:
            {
                break;
            }
            case GuizmoMode::Scale:
            {
                break;  
            }
        };
        
        float QuadSize = 15.f;
        ImVec2 MinCenterPoint = ImVec2(s_Data.ScreenCenter.x - QuadSize, s_Data.ScreenCenter.y - QuadSize);
        ImVec2 MaxCenterPoint = ImVec2(s_Data.ScreenCenter.x + QuadSize, s_Data.ScreenCenter.y + QuadSize);
        
        s_Data.IsCenterPointHovered = ImGui::IsMouseHoveringRect(MinCenterPoint, MaxCenterPoint);

        glm::vec2 AxisSize(100.f, 2.f * QuadSize);
        ImVec2 MinXAxis = ImVec2(s_Data.ScreenCenter.x + QuadSize, s_Data.ScreenCenter.y - QuadSize);
        ImVec2 MaxXAxis = ImVec2(MinXAxis.x + AxisSize.x, MinXAxis.y + AxisSize.y);

        ImVec2 MinYAxis = ImVec2(s_Data.ScreenCenter.x - QuadSize, s_Data.ScreenCenter.y + QuadSize);
        ImVec2 MaxYAxis = ImVec2(MinYAxis.x + AxisSize.y, MinYAxis.y + AxisSize.x);

        s_Data.IsXAxisHovered = ImGui::IsMouseHoveringRect(MinXAxis, MaxXAxis);

        s_Data.IsYAxisHovered = ImGui::IsMouseHoveringRect(MinYAxis, MaxYAxis);
        
        static ImVec2 InitialCursorPosition;
        static glm::vec2 InitialObjectPosition;
        static bool AllowChange = true;
        if (Input::IsMouseButtonPressed(Mouse::Button0))
        {
            if (AllowChange)
            {
                if (s_Data.IsXAxisHovered)
                {
                    AllowChange = false;
                    s_Data.IsMovingX = true;

                    auto[x, y] = ImGui::GetMousePos();
                    InitialCursorPosition = ImVec2(x - s_Data.WindowRectangle.x, y - s_Data.WindowRectangle.y);
                    InitialObjectPosition = s_Data.Transform2D->Position;
                }
                else if (s_Data.IsYAxisHovered)
                {
                    AllowChange = false;
                    s_Data.IsMovingY = true;

                    auto[x, y] = ImGui::GetMousePos();
                    InitialCursorPosition = ImVec2(x - s_Data.WindowRectangle.x, y - s_Data.WindowRectangle.y);
                    InitialObjectPosition = s_Data.Transform2D->Position;
                }
                else if (s_Data.IsCenterPointHovered)
                {
                    AllowChange = false;
                    s_Data.IsDragging = true;
                }
            }
        }
        else
        {
            s_Data.IsDragging = false;
            s_Data.IsMovingX = false;
            s_Data.IsMovingY = false;
            AllowChange = true;
        }
        

        if (s_Data.IsDragging)
        {
            auto[x, y] = ImGui::GetMousePos();
            s_Data.Transform2D->Position = ScreenToWorld(glm::vec2(x - s_Data.WindowRectangle.x, y - s_Data.WindowRectangle.y), s_Data.InverseViewProjection, {s_Data.WindowRectangle.z, s_Data.WindowRectangle.w});
        }
        else if (s_Data.IsMovingX)
        {
            auto[x, y] = ImGui::GetMousePos();
            glm::vec2 worldPosition = ScreenToWorld(glm::vec2(x - s_Data.WindowRectangle.x, y - s_Data.WindowRectangle.y), s_Data.InverseViewProjection, {s_Data.WindowRectangle.z, s_Data.WindowRectangle.w});
            glm::vec2 initialWorldPosition = ScreenToWorld({InitialCursorPosition.x, InitialCursorPosition.y}, s_Data.InverseViewProjection, {s_Data.WindowRectangle.z, s_Data.WindowRectangle.w});
            float newPositionX = InitialObjectPosition.x + worldPosition.x - initialWorldPosition.x;

            s_Data.Transform2D->Position.x = newPositionX; 
        }
        else if (s_Data.IsMovingY)
        {
            auto[x, y] = ImGui::GetMousePos();
            glm::vec2 worldPosition = ScreenToWorld(glm::vec2(x - s_Data.WindowRectangle.x, y - s_Data.WindowRectangle.y), s_Data.InverseViewProjection, {s_Data.WindowRectangle.z, s_Data.WindowRectangle.w});
            glm::vec2 initialWorldPosition = ScreenToWorld({InitialCursorPosition.x, InitialCursorPosition.y}, s_Data.InverseViewProjection, {s_Data.WindowRectangle.z, s_Data.WindowRectangle.w});
            float newPositionY = InitialObjectPosition.y + worldPosition.y - initialWorldPosition.y;

            s_Data.Transform2D->Position.y = newPositionY; 
        }
    }

    void Guizmo::Manipulate2D(const glm::mat3* viewMatrix, const glm::mat3* projectionMatrix, Transform2DComponent *transform, GuizmoMode mode)
    {
        s_Data.Transform2D = transform;
        s_Data.Projection = projectionMatrix;
        s_Data.View = viewMatrix;
        s_Data.Mode = mode;

        InitData();

        HandleInput();

        // bool Dragged = HandleUserInput(objectCenterScreenPos);

        // auto[x, y] = ImGui::GetMousePos();
        // glm::vec2 worldPos = ScreenToWorld(ImVec2(x - s_Data.WindowRectangle.x, y - s_Data.WindowRectangle.y));
        // s_Data.Transform2D->Position = worldPos;

        DrawTranslation2D(s_Data.ScreenCenter);
    }

    glm::vec2 Guizmo::GetObjectCenterWorldPosition(const glm::vec2 screenPosition)
    {
        glm::vec2 ViewportScreenWorldPosition;
        ViewportScreenWorldPosition.x = ConvertValue(screenPosition.x, s_Data.WindowRectangle.x, s_Data.WindowRectangle.x + s_Data.WindowRectangle.z, -1.f, 1.f);
        ViewportScreenWorldPosition.y = ConvertValue(screenPosition.y, s_Data.WindowRectangle.y, s_Data.WindowRectangle.y + s_Data.WindowRectangle.w, 1.f, -1.f);
        return ViewportScreenWorldPosition;
    }

    bool Guizmo::HandleUserInput(const ImVec2& objectCenterScreenPos)
    {
        bool isDragging = false;
        static bool isMouseDown = false;
        static ImVec2 initialMousePos;

        bool isHovered = ImGui::IsMouseHoveringRect(ImVec2(objectCenterScreenPos.x - 15, objectCenterScreenPos.y - 15), ImVec2(objectCenterScreenPos.x + 15, objectCenterScreenPos.y + 15));
        
        if (isHovered && Input::IsMouseButtonPressed(Mouse::Button0) && !isMouseDown)
        {
            isMouseDown = true;
            initialMousePos = ImVec2(Input::GetCursorPosition().first, Input::GetCursorPosition().second);
        }

        // Check for mouse release
        if (!Input::IsMouseButtonPressed(Mouse::Button0))
        {
            isMouseDown = false;
        }

        // Check for mouse drag
        if (isMouseDown)
        {
            ImVec2 MousePosition = ImVec2(Input::GetCursorPosition().first, Input::GetCursorPosition().second);
            ImVec2 delta = ImVec2(MousePosition.x - initialMousePos.x, MousePosition.y - initialMousePos.y);

            // glm::vec2 deltaWorldSpace = ConvertPixelsToWorldSpace(delta);
            glm::vec2 deltaWorldSpace = GetObjectCenterWorldPosition({delta.x, delta.y});
            
            // Apply translation to the object matrix
            if (s_Data.Transform2D != nullptr)
                s_Data.Transform2D->Position += deltaWorldSpace;

            // initialMousePos = MousePosition;

            isDragging = true;
        }

        return isDragging;
    }

    void Guizmo::DrawTranslation2D(const ImVec2& objectCenterScreenPos)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        // Draw X-axis
        drawList->AddLine(objectCenterScreenPos, ImVec2(objectCenterScreenPos.x + 100.0f, objectCenterScreenPos.y), IM_COL32(255, 0, 0, 255), 6.0f);
        drawList->AddCircleFilled(ImVec2(objectCenterScreenPos.x + 100.0f, objectCenterScreenPos.y), s_Data.CircleRadius, IM_COL32(255, 0, 0, 255));

        // Draw Y-axis
        drawList->AddLine(objectCenterScreenPos, ImVec2(objectCenterScreenPos.x, objectCenterScreenPos.y + 100.0f), IM_COL32(0, 255, 0, 255), 6.0f);
        drawList->AddCircleFilled(ImVec2(objectCenterScreenPos.x, objectCenterScreenPos.y + 100.0f), s_Data.CircleRadius, IM_COL32(0, 255, 0, 255));

        // Draw Center Point
        drawList->AddCircleFilled(s_Data.ScreenCenter, (s_Data.IsCenterPointHovered) ? s_Data.CircleRadius + 2.f : s_Data.CircleRadius, IM_COL32(255, 255, 255, 255));
    }

    void Guizmo::DrawRotation2D()
    {

    }

    void Guizmo::DrawScale2D()
    {

    }

    void Guizmo::CalculateColorsAndSizes()
    {

    }

    glm::vec2 Guizmo::ConvertPixelsToWorldSpace(const ImVec2& pixelCoords)
    {
        // auto PositionX = ConvertValue(pixelCoords.x, 0.f, (float)Application::Get().GetWindow().GetWidth(), -1.f, 1.f);
        // auto PositionY = ConvertValue(pixelCoords.y, 0.f, (float)Application::Get().GetWindow().GetHeight(), 1.f, -1.f);
        auto PositionX = ConvertValue(pixelCoords.x, 0.f, s_Data.WindowRectangle.z, -1.f, 1.f);
        auto PositionY = ConvertValue(pixelCoords.y, 0.f, s_Data.WindowRectangle.w, 1.f, -1.f);

        return {PositionX, PositionY};


        // glm::mat3 invProjectionViewMatrix = glm::inverse(*(s_Data.Projection) * *(s_Data.View));

        // // Map pixel coordinates to normalized device coordinates (NDC)
        // glm::vec3 ndcCoords;
        // ndcCoords.x = (2.0f * pixelCoords.x) / s_Data.WindowRectangle.z - 1.0f;
        // ndcCoords.y = 1.0f - (2.0f * pixelCoords.y) / s_Data.WindowRectangle.w;
        // ndcCoords.z = 1.0f;

        // // Map NDC coordinates to world coordinates
        // glm::vec3 worldCoords = invProjectionViewMatrix * ndcCoords;

        // Normalize the result
        // worldCoords /= worldCoords.w;

        // return glm::vec2(worldCoords);
    }

}