#include <Raccoon/Renderer/OrthographicCameraController.h>
#include <Raccoon/Core/Input.h>
#include <Raccoon/Core/Application.h>

#include <Raccoon/Events/MouseEvents.h>
#include <Raccoon/Events/WindowEvents.h>

namespace Raccoon
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
        : m_EnableRotation(rotation),  m_Camera(aspectRatio), m_AspectRatio(aspectRatio)
    {

    }
    
    void OrthographicCameraController::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>([this] (MouseScrolledEvent &event) 
        {
            m_Camera.Zoom(-event.GetYOffset() * 0.25f);
            m_Camera.SetZoom(std::max(m_Camera.GetZoom(), 0.25f));
        });

        dispatcher.Dispatch<WindowResizeEvent>([this] (WindowResizeEvent &event) 
        {
            m_Camera.SetProjection(m_AspectRatio);
        });
    }

    void OrthographicCameraController::OnUpdate(const TimeStep &timestep)
    {
        if (Input::IsKeyPressed(Key::W) || Input::IsKeyPressed(Key::Up))
        {
            m_Camera.AddPositionX(sin(glm::radians(m_Camera.GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
            m_Camera.AddPositionY(cos(glm::radians(m_Camera.GetRotationAngle()))  * m_MoveSpeed * timestep.GetDeltaTime());
        }
        else if (Input::IsKeyPressed(Key::S) || Input::IsKeyPressed(Key::Down))
        {
            m_Camera.AddPositionX(-sin(glm::radians(m_Camera.GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
            m_Camera.AddPositionY(-cos(glm::radians(m_Camera.GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
        }

        if (Input::IsKeyPressed(Key::A) || Input::IsKeyPressed(Key::Left))
        {
            m_Camera.AddPositionX(-cos(glm::radians(m_Camera.GetRotationAngle()))  * m_MoveSpeed * timestep.GetDeltaTime());
            m_Camera.AddPositionY(-sin(glm::radians(m_Camera.GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
        }
        else if (Input::IsKeyPressed(Key::D) || Input::IsKeyPressed(Key::Right))
        {
            m_Camera.AddPositionX(cos(glm::radians(m_Camera.GetRotationAngle()))  * m_MoveSpeed * timestep.GetDeltaTime());
            m_Camera.AddPositionY(sin(glm::radians(m_Camera.GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
        }

        if (m_EnableRotation)
        {
            if (Input::IsKeyPressed(Key::Q))
				m_Camera.Rotate(m_RotationSpeed * timestep.GetDeltaTime());
			if (Input::IsKeyPressed(Key::E))
				m_Camera.Rotate(-m_RotationSpeed * timestep.GetDeltaTime());

			if (m_Camera.GetRotationAngle() > 180.0f)
				m_Camera.Rotate(-360.0f);
			else if (m_Camera.GetRotationAngle() <= -180.0f)
				m_Camera.Rotate(360.0f);
        }
    }
}