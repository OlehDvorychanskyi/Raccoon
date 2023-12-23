#pragma once 
#include <Raccoon/Scene/Scene.h>
// #include <Raccoon/Scene/Registry.h>
#include <entt.hpp>

#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
	class HierarchyPanel;
	class Registry;

    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity id, Scene* scene);

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            RE_CORE_ASSERT(!HasComponent<T>(), "Entity already has a component!");

			T& component = m_Scene->m_Registry.GetRegistry().emplace<T>(m_ID, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);

			return component;
        }

        template<typename T>
		T& GetComponent()
		{
			RE_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have a component!");
			return m_Scene->m_Registry.GetRegistry().get<T>(m_ID);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.GetRegistry().all_of<T>(m_ID);
		}

		template<typename T>
		void RemoveComponent()
		{
			RE_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have a component!");

			m_Scene->OnComponentRemoved<T>(GetComponent<T>());
			m_Scene->m_Registry.GetRegistry().remove<T>(m_ID);
		}

		operator entt::entity() const { return m_ID; }
		operator uint32_t() const { return (uint32_t)m_ID; }
		operator bool() const { return m_ID != entt::null; }

		bool operator==(const Entity& other) const { return m_ID == other.m_ID && m_Scene == other.m_Scene; }
		bool operator!=(const Entity& other) const { return !(*this == other); }
    private:	
        entt::entity m_ID = entt::null;
        Scene *m_Scene = nullptr; // like a weak pointer

		friend class HierarchyPanel;
		friend class Registry; 
    };
}