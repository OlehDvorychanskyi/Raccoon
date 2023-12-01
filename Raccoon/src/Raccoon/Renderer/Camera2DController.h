#pragma once 
#include <Raccoon/Renderer/Cameras.h>
#include <Raccoon/Core/TimeStep.h>
#include <memory>

namespace Raccoon
{
    // class Camera2DController
    // {
    // public:
    //     Camera2DController(const std::shared_ptr<Camera2D> &camera, bool rotation = false);

    //     void OnEvent(Event &event);
    //     void OnUpdate(const TimeStep &timestep);

    //     void SetMoveSpeed(float speed) { m_MoveSpeed = speed; }
    //     void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }
    //     void SetZoomSpeed(float speed) { m_ZoomSpeed = speed; }
        
    //     const std::shared_ptr<Camera2D>& GetCamera() const { return m_Camera; }
    //     std::shared_ptr<Camera2D>& GetCamera() { return m_Camera; }
    // private:
    //     std::shared_ptr<Camera2D> m_Camera;
    //     float m_MoveSpeed = 5.f, m_RotationSpeed = 40.f, m_ZoomSpeed = 1.f;
    //     bool m_EnableRotation;
    // };
}