#include <Raccoon/Renderer/Camera2DController.h>
#include <Raccoon/Core/Input.h>

#include <Raccoon/Events/MouseEvents.h>


namespace Raccoon
{
    // Camera2DController::Camera2DController(const std::shared_ptr<Camera2D> &camera, bool rotation)  
    //     : m_Camera{camera}, m_EnableRotation{rotation}
    // {
        
    // }

    // void Camera2DController::OnEvent(Event &event)
    // {
    //     EventDispatcher dispatcher(event);
	// 	dispatcher.Dispatch<MouseScrolledEvent>([this] (MouseScrolledEvent &event) 
    //     {
    //         m_Camera->AddZoom(-event.GetYOffset() * 0.25f);
    //         m_Camera->SetZoom(std::max(m_Camera->GetZoom(), 0.25f));
    //     });

    //     m_Camera->OnEvent(event);
    // }

    // void Camera2DController::OnUpdate(const TimeStep &timestep)
    // {
    //     if (Input::IsKeyPressed(Key::W) || Input::IsKeyPressed(Key::Up))
    //     {
    //         m_Camera->AddPositionX(sin(glm::radians(m_Camera->GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
    //         m_Camera->AddPositionY(cos(glm::radians(m_Camera->GetRotationAngle()))  * m_MoveSpeed * timestep.GetDeltaTime());
    //     }
    //     else if (Input::IsKeyPressed(Key::S) || Input::IsKeyPressed(Key::Down))
    //     {
    //         m_Camera->AddPositionX(-sin(glm::radians(m_Camera->GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
    //         m_Camera->AddPositionY(-cos(glm::radians(m_Camera->GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
    //     }

    //     if (Input::IsKeyPressed(Key::A) || Input::IsKeyPressed(Key::Left))
    //     {
    //         m_Camera->AddPositionX(-cos(glm::radians(m_Camera->GetRotationAngle()))  * m_MoveSpeed * timestep.GetDeltaTime());
    //         m_Camera->AddPositionY(-sin(glm::radians(m_Camera->GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
    //     }
    //     else if (Input::IsKeyPressed(Key::D) || Input::IsKeyPressed(Key::Right))
    //     {
    //         m_Camera->AddPositionX(cos(glm::radians(m_Camera->GetRotationAngle()))  * m_MoveSpeed * timestep.GetDeltaTime());
    //         m_Camera->AddPositionY(sin(glm::radians(m_Camera->GetRotationAngle())) * m_MoveSpeed * timestep.GetDeltaTime());
    //     }

    //     if (m_EnableRotation)
    //     {
    //         if (Input::IsKeyPressed(Key::Q))
	// 			m_Camera->Rotate(m_RotationSpeed * timestep.GetDeltaTime());
	// 		if (Input::IsKeyPressed(Key::E))
	// 			m_Camera->Rotate(-m_RotationSpeed * timestep.GetDeltaTime());

	// 		if (m_Camera->GetRotationAngle() > 180.0f)
	// 			m_Camera->Rotate(-360.0f);
	// 		else if (m_Camera->GetRotationAngle() <= -180.0f)
	// 			m_Camera->Rotate(360.0f);
    //     }
    //     else
    //     {
    //         // TODO:
    //     }
    // }
}