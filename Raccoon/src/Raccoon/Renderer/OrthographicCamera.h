#pragma once 
#include <glm/glm.hpp>

namespace Raccoon
{
    // class OrthographicCamera 
    // {
    // public:
    //     OrthographicCamera(float aspectRatio, const glm::vec3 &position = {0.f, 0.f, 0.f});

    //     void Update(); 

    //     const glm::mat4& GetViewMatrix() const { return m_View; }
    //     const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
    //     const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjection; }

    //     void SetProjection(float aspectRatio);

    //     void AddPosition(const glm::vec3 &position);
    //     void AddPositionX(float x);
    //     void AddPositionY(float y);
    //     void AddPositionZ(float z);
    //     void SetPosition(const glm::vec3 &position);
    //     const glm::vec3& GetPosition() const { return m_Position; }

    //     void Rotate(float angle);
    //     void SetRotationAngle(float angle); 
    //     float GetRotationAngle() const { return m_RotationAngle; }

    //     void Zoom(float zoom);
    //     void SetZoom(float zoom);
    //     float GetZoom() const { return m_Zoom; }
    // private:
    //     glm::mat4 m_View;
    //     glm::mat4 m_Projection;
    //     glm::mat4 m_ViewProjection;

    //     glm::vec3 m_Position;

    //     bool m_Zoomed = false, m_Moved = false;
    //     float m_RotationAngle = 0.f, m_AspectRatio, m_Zoom = 1.f;
    // };
}