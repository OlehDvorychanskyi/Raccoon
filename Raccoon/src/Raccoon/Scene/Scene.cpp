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

    std::size_t Scene::GetEntityOrder(entt::entity entity) const 
    {
        return m_Registry.GetEntityIndex(entity);
    }

    void Scene::ChangeEntityPosition(entt::entity entity, std::size_t newPosition) 
    {
        m_Registry.ChangeEntityPosition(entity, newPosition);
    }

    void Scene::OnEditorBegin()
    {

    }

    void Scene::OnRuntimeBegin()
    {
        m_Running = true;

        {
            auto scripts = m_Registry.GetRegistry().group<>(entt::get<NativeScriptComponent>);
            for (entt::entity entity : scripts) 
            {
                auto& script = m_Registry.GetRegistry().get<NativeScriptComponent>(entity);
                if (script.Script == nullptr)
                {
                    script.Script = script.CreateScript();
                    script.Script->m_Entity = Entity{entity, this};
                    script.Script->OnCreate();
                }
            }
        }
    }

    void Scene::OnEditorEnd()
    {
        
    }
    
    void Scene::OnRuntimeEnd()
    {
        m_Running = false;
    }

    void Scene::OnEditorUpdate(const TimeStep &timestep, EditorCamera &camera)
    {
        {
            auto transforms = m_Registry.GetRegistry().group<>(entt::get<Transform2DComponent>);
            for (entt::entity entity : transforms) 
            {
                auto& transform = m_Registry.GetRegistry().get<Transform2DComponent>(entity);
                transform.OnUpdate();
            }
        }

        RenderScene(camera);
    }

    void Scene::OnRuntimeUpdate(const TimeStep &timestep)
    {
        // Update Native Scripts
        {
            auto scripts = m_Registry.GetRegistry().group<>(entt::get<NativeScriptComponent, Transform2DComponent>);
            for (entt::entity entity : scripts) 
            {
                auto& script = m_Registry.GetRegistry().get<NativeScriptComponent>(entity);
                if (script.Script == nullptr)
                {
                    script.Script = script.CreateScript();
                    script.Script->m_Entity = Entity{entity, this};
                    script.Script->OnCreate();
                }
                script.Script->OnUpdate(timestep);
            }
        }

        // Update
        {
            auto entityControllers = m_Registry.GetRegistry().group<>(entt::get<EntityControllerComponent>);
            for (entt::entity entity : entityControllers) 
            {
                auto& controller = m_Registry.GetRegistry().get<EntityControllerComponent>(entity);
                controller.OnUpdate(timestep);
            }
        }

        {
            auto transforms = m_Registry.GetRegistry().group<>(entt::get<Transform2DComponent>);
            for (entt::entity entity : transforms) 
            {
                auto& transform = m_Registry.GetRegistry().get<Transform2DComponent>(entity);
                transform.OnUpdate();
            }
        }

        // Runtime Render2D
        if (m_PrimaryCamera.Camera)
        {
            RenderScene(*m_PrimaryCamera.Camera, *m_PrimaryCamera.Transform); 
        }
    }

    void Scene::RenderScene(EditorCamera &camera)
    {
        Renderer2D::Begin(camera);
        RenderScene();
        Renderer2D::End();
    }

    void Scene::RenderScene(Camera2D &camera, const glm::mat3 &transform)
    {
        Renderer2D::Begin(camera, transform);
        RenderScene();
        Renderer2D::End();
    }

    void Scene::RenderScene()
    {
        auto drawable = m_Registry.GetRegistry().group<>(entt::get<ZComponent>);

        drawable.sort([this](entt::entity a, entt::entity b) 
        {
            uint32_t zIndexA = m_Registry.GetRegistry().get<ZComponent>(a).ZIndex;
            uint32_t zIndexB = m_Registry.GetRegistry().get<ZComponent>(b).ZIndex;

            // Compare by ZIndex first
            if (zIndexA != zIndexB) 
                return zIndexA < zIndexB;

            // If ZIndex is the same, compare by entity order
            return GetEntityOrder(a) < GetEntityOrder(b);
        });

        for (entt::entity entity : drawable) 
        {
            if (m_Registry.GetRegistry().all_of<SpriteRendererComponent>(entity))
            {
                auto [sprite, transform] = m_Registry.GetRegistry().get<SpriteRendererComponent, Transform2DComponent>(entity);
                Renderer2D::DrawRectangle(transform.GetTransform(), sprite.Texture, sprite.Color);
            }
            else if (m_Registry.GetRegistry().all_of<ColorRendererComponent>(entity))
            {
                auto [sprite, transform] = m_Registry.GetRegistry().get<ColorRendererComponent, Transform2DComponent>(entity);
                Renderer2D::DrawRectangle(transform.GetTransform(), sprite.Color);
            }
        }
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        if (m_ViewportWidth == width && m_ViewportHeight == height)
            return;
        
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        auto cameras = m_Registry.GetRegistry().group<>(entt::get<OrthographicCameraComponent>);
        for (entt::entity entity : cameras)
        {
            auto& cameraComponent = cameras.get<OrthographicCameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetAspectRatio(width, height);
        }
    }
        
    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity {m_Registry.CreateEntity(), this};
        entity.AddComponent<Transform2DComponent>();
        entity.AddComponent<NameComponent>(name);

        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        if (entity.HasComponent<OrthographicCameraComponent>())
            if (HasPrimaryCamera()) 
                if (IsPrimaryCamera(&entity.GetComponent<OrthographicCameraComponent>().Camera))
                    SetPrimaryCamera(nullptr, nullptr);
        
        m_Registry.DestroyEntity(entity);
    }

    void Scene::SetPrimaryCamera(Camera2D* camera, glm::mat3 *transform)
    {       
        m_PrimaryCamera.Camera = camera;
        m_PrimaryCamera.Transform = transform;
    }

    template<>
    void Scene::OnComponentAdded<Transform2DComponent>(Entity entity, Transform2DComponent& component)
    {
        
    }

    template<>
    void Scene::OnComponentRemoved<Transform2DComponent>(Entity entity, Transform2DComponent& component)
    {
        
    }
    
    template<>
    void Scene::OnComponentAdded<NameComponent>(Entity entity, NameComponent& component)
    {
        
    }

    template<>
    void Scene::OnComponentRemoved<NameComponent>(Entity entity, NameComponent& component)
    {
        
    }
    
    template<>
    void Scene::OnComponentAdded<ZComponent>(Entity entity, ZComponent& component)
    {
        
    }
    
    template<>
    void Scene::OnComponentRemoved<ZComponent>(Entity entity, ZComponent& component)
    {
        
    }
    
    template<>
    void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {
        if (!entity.HasComponent<ZComponent>())
            entity.AddComponent<ZComponent>();
    }

    template<>
    void Scene::OnComponentRemoved<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {
        if (!entity.HasComponent<ColorRendererComponent>() && entity.HasComponent<ZComponent>())
            entity.RemoveComponent<ZComponent>();
    }
    
    template<>
    void Scene::OnComponentAdded<ColorRendererComponent>(Entity entity, ColorRendererComponent& component)
    {
        if (!entity.HasComponent<ZComponent>())
            entity.AddComponent<ZComponent>();
    }

    template<>
    void Scene::OnComponentRemoved<ColorRendererComponent>(Entity entity, ColorRendererComponent& component)
    {
        if (!entity.HasComponent<SpriteRendererComponent>() && entity.HasComponent<ZComponent>())
            entity.RemoveComponent<ZComponent>();
    }
        
    template<>
    void Scene::OnComponentAdded<OrthographicCameraComponent>(Entity entity, OrthographicCameraComponent& component)
    {
        if (!HasPrimaryCamera())
        {
            m_PrimaryCamera.Camera = &component.Camera;
            m_PrimaryCamera.Transform = &entity.GetComponent<Transform2DComponent>().GetTransform();
        }
    }

    template<>
    void Scene::OnComponentRemoved<OrthographicCameraComponent>(Entity entity, OrthographicCameraComponent& component)
    {
        if (IsPrimaryCamera(&component.Camera))
            SetPrimaryCamera(nullptr, nullptr);
    }

    template<>
    void Scene::OnComponentAdded<EntityControllerComponent>(Entity entity, EntityControllerComponent& component)
    {
        component.SetTransformComponent(m_Registry.GetRegistry().get<Transform2DComponent>(entity));
    }
    
    template<>
    void Scene::OnComponentRemoved<EntityControllerComponent>(Entity entity, EntityControllerComponent& component)
    {
        component.SetTransformComponent(m_Registry.GetRegistry().get<Transform2DComponent>(entity));
    }

    template<>
    void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {
        
    }
    
    template<>
    void Scene::OnComponentRemoved<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {
        
    }
}
