#include <Raccoon/Scene/Scene.h>
#include <Raccoon/Scene/Components.h>
#include <Raccoon/Scene/Entity.h>

#include <Raccoon/Renderer/Renderer2D.h>

#include <algorithm>

namespace Raccoon
{
    Scene::Scene()
    {

    }

    Scene::~Scene()
    {

    }

    void Scene::OnUpdate(const TimeStep &timestep)
    {
        OrthographicCamera* m_ActiveCamera = nullptr;
        glm::mat4 m_Transform;
        {
            auto cameras = m_Registry.group<>(entt::get<OrthographicCameraComponent, Transform2DComponent>);
            for (entt::entity entity : cameras) 
            {
                auto [camera, transform] = m_Registry.get<OrthographicCameraComponent, Transform2DComponent>(entity);
                if (camera.ActiveCamera)
                {
                    m_ActiveCamera = &camera.Camera;
                    m_Transform = transform.GetTransform();
                }
            }
        }

        // Renderer2D
        if (m_ActiveCamera)
        {
            Renderer2D::Begin(*m_ActiveCamera, m_Transform);

            auto drawable = m_Registry.group<>(entt::get<ZComponent>);

            drawable.sort([this](entt::entity a, entt::entity b) 
            {
                return m_Registry.get<ZComponent>(a).ZIndex < m_Registry.get<ZComponent>(b).ZIndex;
            });

            for (entt::entity entity : drawable) 
            {
                if (m_Registry.all_of<SpriteRendererComponent, Transform2DComponent>(entity))
                {
                    auto [sprite, transform] = m_Registry.get<SpriteRendererComponent, Transform2DComponent>(entity);
                    Renderer2D::DrawRectangle(transform.GetTransform(), sprite.Texture);
                }
                else if (m_Registry.all_of<ColorRendererComponent, Transform2DComponent>(entity))
                {
                    auto [sprite, transform] = m_Registry.get<ColorRendererComponent, Transform2DComponent>(entity);
                    Renderer2D::DrawRectangle(transform.GetTransform(), sprite.Color);
                }
            }

            Renderer2D::End();
        }
    }   
        
    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity {m_Registry.create(), this};
        entity.AddComponent<Transform2DComponent>();
        entity.AddComponent<NameComponent>();

        return entity;
    }

    template<typename T>
    void Scene::OnComponentAdded(Entity entity, T& component)
    {
        RE_CORE_ASSERT(sizeof(T) != 0);
    }

    template<>
    void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {
        m_Registry.emplace<ZComponent>(entity);
    }

    template<>
    void Scene::OnComponentAdded<ColorRendererComponent>(Entity entity, ColorRendererComponent& component)
    {
        m_Registry.emplace<ZComponent>(entity);
    }

    template<>
    void Scene::OnComponentAdded<OrthographicCameraComponent>(Entity entity, OrthographicCameraComponent& component)
    {
        
    }
}