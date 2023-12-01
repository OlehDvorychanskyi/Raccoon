#include <Raccoon/Renderer/Cameras.h>
#include <Raccoon/Events/WindowEvents.h>

#include <glm/gtx/matrix_transform_2d.hpp>

#include <Raccoon/Math/Ortho.h>

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
            m_RecalculateProjection = true;
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
}