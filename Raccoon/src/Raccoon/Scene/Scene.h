#pragma once
#include <Raccoon/Core/TimeStep.h>
#include <Raccoon/Events/Event.h>
#include <entt.hpp> 
#include <cstdint>
#include <glm/glm.hpp>
#include <Raccoon/Renderer/Cameras.h>
#include <Raccoon/Core/Assert.h>

#include <Raccoon/Scene/Registry.h>

namespace Raccoon
{
    class Entity;
    class HierarchyPanel;
    class SceneSerializer;

    class Scene 
    {
    public:
        Scene();
        ~Scene();

        void OnEditorBegin();
        void OnRuntimeBegin();

        void OnEditorEnd();
        void OnRuntimeEnd();

        void OnEditorUpdate(const TimeStep &timestep, EditorCamera &camera);
        void OnRuntimeUpdate(const TimeStep &timestep);

        void OnViewportResize(uint32_t width, uint32_t height);
        
        Entity CreateEntity(const std::string& name = std::string());
        void DestroyEntity(Entity entity);

        void SetPrimaryCamera(Camera2D* camera, glm::mat3 *transform);
        bool IsPrimaryCamera(Camera2D* camera) const { RE_CORE_ASSERT(HasPrimaryCamera(), "Scene doesn't have primary camera"); return m_PrimaryCamera.Camera == camera; }
        bool HasPrimaryCamera() const { return m_PrimaryCamera.Camera != nullptr; }

        Camera2D* GetPrimaryCamera() { return m_PrimaryCamera.Camera; }
        glm::mat3* GetPrimaryCameraTransform() { return m_PrimaryCamera.Transform; }
    private:
        template<typename T>
		void OnComponentAdded(Entity entity, T& component);

        template<typename T>
		void OnComponentRemoved(Entity entity, T& component);

        std::size_t GetEntityOrder(entt::entity entity) const;
        void ChangeEntityPosition(entt::entity entity, std::size_t newPosition);

        void RenderScene(Camera2D &camera, const glm::mat3 &transform);
        void RenderScene(EditorCamera &camera);
        void RenderScene();
    private:    
        Registry m_Registry;
        uint32_t m_ViewportWidth = 0u, m_ViewportHeight = 0u;

        struct Camera
        {
            Camera2D *Camera = nullptr;
            glm::mat3 *Transform = nullptr;
        };
        Camera m_PrimaryCamera;

        bool m_Running = false;
        bool m_Pause = false;

        friend class Entity;
        friend class HierarchyPanel;
        friend class SceneSerializer;
    };
}