#pragma once 
#include <Raccoon/Core/TimeStep.h>
#include <Raccoon/Events/Event.h>
#include <Raccoon/Renderer/OrthographicCamera.h>

namespace Raccoon
{
    class OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnEvent(Event &event);
        void OnUpdate(const TimeStep &timestep);

        void SetMoveSpeed(float speed)     { m_MoveSpeed = speed; }
        void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }
        void SetZoomSpeed(float speed)     { m_ZoomSpeed = speed; }

        const OrthographicCamera& GetCamera() const { return m_Camera; }
        OrthographicCamera& GetCamera() { return m_Camera; }
    private:
        float m_MoveSpeed = 5.f, m_RotationSpeed = 40.f, m_ZoomSpeed = 1.f, m_AspectRatio;
        bool m_EnableRotation;
        OrthographicCamera m_Camera;
    };
}