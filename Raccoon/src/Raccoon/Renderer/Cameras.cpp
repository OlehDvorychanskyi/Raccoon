#include <Raccoon/Renderer/Cameras.h>
#include <Raccoon/Events/WindowEvents.h>
#include <Raccoon/Events/MouseEvents.h>
#include <Raccoon/Core/Input.h>
#include <Raccoon/Core/Base.h>

#include <glm/gtx/matrix_transform_2d.hpp>

#include <Raccoon/Math/Math.h>

#include <Raccoon/Core/Assert.h>

#include <imgui.h>

namespace Raccoon
{
    // ----------------------- ORTHOGRAPHIC CAMERA -----------------------------------------------------------------------------------------

    OrthographicCamera::OrthographicCamera()
        : m_AspectRatio{1.f}, m_OrthographicSize{1.f}
    {
        RecalculateProjection();
    }

    OrthographicCamera::OrthographicCamera(float aspectRatio, float orthographicSize)
        : m_AspectRatio{aspectRatio}, m_OrthographicSize{orthographicSize} 
    {
        RecalculateProjection();
    }

    OrthographicCamera::OrthographicCamera(uint32_t width, uint32_t height, float orthographicSize)
        : m_OrthographicSize{orthographicSize} 
    {
        m_AspectRatio = (float)width / (float)height;
        RecalculateProjection();
    }

    void OrthographicCamera::OnUpdate()
    {
        if (m_RecalculateProjection)
        {
            RecalculateProjection();
            m_RecalculateProjection = false;
        }
    }

    void OrthographicCamera::SetAspectRatio(float ratio)
    {
        if (ratio != m_AspectRatio)
        {
            m_AspectRatio = ratio;
            m_RecalculateProjection = true;
        }
    }

    void OrthographicCamera::SetAspectRatio(uint32_t width, uint32_t height)
    {
        float ratio = (float)width / (float)height; 
        if (ratio != m_AspectRatio)
        {
            m_AspectRatio = ratio;
            m_RecalculateProjection = true;
        }
    }

    void OrthographicCamera::SetOrthographicSize(float size)
    {
        if (size != m_OrthographicSize)
        {
            m_OrthographicSize = size;
            m_RecalculateProjection = true;
        }
    }

    void OrthographicCamera::RecalculateProjection()
    {
        float orthoLeft = -m_OrthographicSize * m_AspectRatio;
        float orthoRight = m_OrthographicSize * m_AspectRatio;
        float orthoBottom = -m_OrthographicSize;
        float orthoTop = m_OrthographicSize;

        m_Projection = Raccoon::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop);
    }
    
    // -------------------------------------------------------------------------------------------------------------------------------------
    
    // ----------------------- EDITOR CAMERA -----------------------------------------------------------------------------------------------
        
        EditorCamera::EditorCamera()
        {
            RecalculateProjection();
        }
        
        EditorCamera::EditorCamera(float aspectRatio, float zoom, bool fixedAspectRatio)
            : m_AspectRatio{aspectRatio}, m_Zoom{zoom}, m_FixedAspectRatio{fixedAspectRatio}
        {
            RecalculateProjection();
        }

        
        EditorCamera::EditorCamera(uint32_t width, uint32_t height, float zoom, bool fixedAspectRatio)
            : m_Zoom{zoom}, m_FixedAspectRatio{fixedAspectRatio}
        {
            m_AspectRatio = (float)width / (float)height;
            RecalculateProjection();
        }

        void EditorCamera::OnUpdateController(const TimeStep &ts, const glm::vec2 &viewportSize, const glm::vec2 &viewportPosition)
        {
            static bool first = true;

            if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
            {
                auto mainWindowCursorPosition = Input::GetCursorGlobalPosition();
                glm::vec2 cursorPosition{ mainWindowCursorPosition.x - viewportPosition.x, mainWindowCursorPosition.y - viewportPosition.y };

                if (first)
                {   
                    m_CursorPosition = cursorPosition;
                    first = false;
                }

                auto inverseProjection = glm::inverse(m_Projection);

                glm::vec2 worldPos1 = ScreenToWorld(cursorPosition, inverseProjection, viewportSize);
                glm::vec2 worldPos2 = ScreenToWorld(m_CursorPosition, inverseProjection, viewportSize);
                
                glm::vec2 delta = worldPos1 - worldPos2;

                AddPosition(-delta);

                m_CursorPosition = cursorPosition;     
            }
            else
            {
                first = true;
            }
        }

        void EditorCamera::OnUpdate()
        {  
            if (m_RecalculateView)
            {
                RecalculateView();
                m_RecalculateView = false;
            }

            if (!m_FixedAspectRatio && m_RecalculateProjection)
            {
                RecalculateProjection();
                m_RecalculateProjection = false;
            }
        }

        void EditorCamera::OnEvent(Event &event)
        {
            EventDispatcher dispatcher(event);
            dispatcher.Dispatch<MouseScrolledEvent>([this] (MouseScrolledEvent &event) 
            {
                AddZoom(-event.GetYOffset() * 0.25f);
                SetZoom(std::max(m_Zoom, 0.25f));
            });
        }

        void EditorCamera::SetAspectRatio(float ratio)
        {
            if (ratio != m_AspectRatio)
            {
                m_AspectRatio = ratio;
                m_RecalculateProjection = true;
            }
        }

        void EditorCamera::SetAspectRatio(uint32_t width, uint32_t height)
        {
            float ratio = (float)width / (float)height; 
            if (ratio != m_AspectRatio)
            {
                m_AspectRatio = ratio;
                m_RecalculateProjection = true;
            }
        }

        void EditorCamera::RecalculateProjection()
        {
            float orthoLeft = -m_Zoom * m_AspectRatio;
            float orthoRight = m_Zoom * m_AspectRatio;
            float orthoBottom = -m_Zoom;
            float orthoTop = m_Zoom;

            m_Projection = Raccoon::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop);
        }

        void EditorCamera::RecalculateView()
        {
            auto transform = glm::translate(glm::mat3(1.f), m_Position);
            m_View = glm::inverse(transform);
        }

        void EditorCamera::SetPosition(const glm::vec2 &position) 
        { 
            if (m_Position != position) 
            {
                m_Position = position;
                m_RecalculateView = true;
            }
        }
        
        void EditorCamera::AddPosition(const glm::vec2 &position) 
        { 
            if (position != glm::vec2(0.f, 0.f)) 
            {
                m_Position += position;
                m_RecalculateView = true;
            }    
        }

        void EditorCamera::AddPositionX(float x) 
        {
            if (x != 0.f) 
            {
                m_Position.x += x;
                m_RecalculateView = true;
            }           
        }

        void EditorCamera::AddPositionY(float y) 
        {
            if (y != 0.f) 
            {
                m_Position.y += y;
                m_RecalculateView = true;
            }
        }

        void EditorCamera::AddZoom(float zoom) 
        { 
            if (zoom != 0.f)
            { 
                m_Zoom += zoom; 
                m_RecalculateProjection = true; 
            }
        }

        void EditorCamera::SetZoom(float zoom)
        {
            if (m_Zoom != zoom)
            { 
                m_Zoom = zoom; 
                m_RecalculateProjection = true; 
            }
        }
    // -------------------------------------------------------------------------------------------------------------------------------------
}