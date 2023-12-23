#include <Raccoon/Scene/Components.h>
#include <Raccoon/Core/Input.h>


#include <glm/glm.hpp>

namespace Raccoon
{
    // ----------------------- EntityControllerComponent -------------------------------------------------------------------------------------------------
        
        EntityControllerComponent::EntityControllerComponent(Transform2DComponent &transform, bool enableRotation)
            : m_EnableRotation{enableRotation}
        {
            m_Transform = &transform;
        }

        void EntityControllerComponent::OnUpdate(const TimeStep &timestep)
        {
            if (Input::IsKeyPressed(Key::W) || Input::IsKeyPressed(Key::Up))
            {
                m_Transform->Position.x += sin(glm::radians(m_Transform->RotationAngle)) * m_MoveSpeed * timestep.GetDeltaTime();
                m_Transform->Position.y += cos(glm::radians(m_Transform->RotationAngle)) * m_MoveSpeed * timestep.GetDeltaTime();
            }
            else if (Input::IsKeyPressed(Key::S) || Input::IsKeyPressed(Key::Down))
            {
                m_Transform->Position.x -= sin(glm::radians(m_Transform->RotationAngle)) * m_MoveSpeed * timestep.GetDeltaTime();
                m_Transform->Position.y -= cos(glm::radians(m_Transform->RotationAngle)) * m_MoveSpeed * timestep.GetDeltaTime();
            }

            if (Input::IsKeyPressed(Key::A) || Input::IsKeyPressed(Key::Left))
            {
                m_Transform->Position.x -= cos(glm::radians(m_Transform->RotationAngle)) * m_MoveSpeed * timestep.GetDeltaTime();
                m_Transform->Position.y -= sin(glm::radians(m_Transform->RotationAngle)) * m_MoveSpeed * timestep.GetDeltaTime();
            }
            else if (Input::IsKeyPressed(Key::D) || Input::IsKeyPressed(Key::Right))
            {
                m_Transform->Position.x += cos(glm::radians(m_Transform->RotationAngle)) * m_MoveSpeed * timestep.GetDeltaTime();
                m_Transform->Position.y += sin(glm::radians(m_Transform->RotationAngle)) * m_MoveSpeed * timestep.GetDeltaTime();
            }

            if (m_EnableRotation)
            {
                if (Input::IsKeyPressed(Key::Q))
                    m_Transform->RotationAngle += m_RotationSpeed * timestep.GetDeltaTime();
                if (Input::IsKeyPressed(Key::E))
                    m_Transform->RotationAngle -= m_RotationSpeed * timestep.GetDeltaTime();

                if (m_Transform->RotationAngle > 180.0f)
                    m_Transform->RotationAngle -= 360.0f;
                else if (m_Transform->RotationAngle <= -180.0f)
                    m_Transform->RotationAngle += 360.0f;
            }
        }

    // ---------------------------------------------------------------------------------------------------------------------------------------------------
    
    // ----------------------- ParentEntityComponent -----------------------------------------------------------------------------------------------------
        
        void ParentEntityComponent::AddChild(const std::shared_ptr<Entity> &child)
        {
            m_Childrens.push_back(child);
        }
    
    // ---------------------------------------------------------------------------------------------------------------------------------------------------
}