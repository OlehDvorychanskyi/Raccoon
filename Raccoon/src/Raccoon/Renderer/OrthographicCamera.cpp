#include <Raccoon/Renderer/OrthographicCamera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Raccoon
{
    // OrthographicCamera::OrthographicCamera(float aspectRatio, const glm::vec3 &position)
    //     : m_Position{position}, m_AspectRatio{aspectRatio}
    // {
    //     m_View = glm::inverse(glm::translate(glm::mat4(1.f), m_Position));
    //     m_Projection = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    //     m_ViewProjection = m_Projection * m_View;
    // }

    // void OrthographicCamera::SetProjection(float aspectRatio)
    // {
    //     m_AspectRatio = aspectRatio;
    //     m_Projection = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    //     m_ViewProjection = m_Projection * m_View;
    // }

    // void OrthographicCamera::Update()
    // {
    //     if (m_Moved)
    //     {
    //         auto transform = glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), glm::radians(m_RotationAngle), glm::vec3(0.f, 0.f, 1.f));
    //         m_View = glm::inverse(transform);
    //         m_Moved = false;
    //     }

    //     if (m_Zoomed)
    //     {
    //         m_Projection = glm::ortho(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
    //         m_Zoomed = false;
    //     }
        
    //     m_ViewProjection = m_Projection * m_View;
    // }

    // void OrthographicCamera::SetPosition(const glm::vec3 &position) 
    // { 
    //     if (m_Position != position) 
    //     {
    //         m_Position = position;
    //         m_Moved = true;
    //     }
    // }
    
    // void OrthographicCamera::AddPosition(const glm::vec3 &position) 
    // { 
    //     if (position != glm::vec3(0.f, 0.f, 0.f)) 
    //     {
    //         m_Position += position;
    //         m_Moved = true;
    //     }    
    // }

    // void OrthographicCamera::AddPositionX(float x) 
    // {
    //     if (x != 0.f) 
    //     {
    //         m_Position.x += x;
    //         m_Moved = true;
    //     }           
    // }

    // void OrthographicCamera::AddPositionY(float y) 
    // {
    //     if (y != 0.f) 
    //     {
    //         m_Position.y += y;
    //         m_Moved = true;
    //     }
    // }

    // void OrthographicCamera::AddPositionZ(float z) 
    // {
    //     if (z != 0.f) 
    //     {
    //         m_Position.z += z;
    //         m_Moved = true;
    //     }
    // }
    
    // void OrthographicCamera::SetRotationAngle(float angle) 
    // { 
    //     if (m_RotationAngle != angle) 
    //     {
    //         m_RotationAngle = angle;
    //         m_Moved = true;
    //     }
    // }
    // void OrthographicCamera::Rotate(float angle) 
    // { 
    //     if (angle != 0.f)
    //     {
    //         m_RotationAngle += angle; 
    //         m_Moved = true;
    //     } 
    // }

    // void OrthographicCamera::Zoom(float zoom) 
    // { 
    //     if (zoom != 0.f)
    //     { 
    //         m_Zoom += zoom; 
    //         m_Zoomed = true; 
    //     }
    // }

    // void OrthographicCamera::SetZoom(float zoom)
    // {
    //     if (m_Zoom != zoom)
    //     { 
    //         m_Zoom = zoom; 
    //         m_Zoomed = true; 
    //     }
    // }
}