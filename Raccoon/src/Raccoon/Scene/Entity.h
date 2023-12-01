#pragma once 
#include <Raccoon/Scene/Scene.h>
#include <entt.hpp>

#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity id, Scene* scene);

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            RE_CORE_ASSERT(!HasComponent<T>(), "Entity already has a component!");

			T& component = m_Scene->m_Registry.emplace<T>(m_ID, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);

			return component;
        }

        template<typename T>
		T& GetComponent()
		{
			RE_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have a component!");
			return m_Scene->m_Registry.get<T>(m_ID);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_ID);
		}

		template<typename T>
		void RemoveComponent()
		{
			RE_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have a component!");
			m_Scene->m_Registry.remove<T>(m_ID);
		}

		operator entt::entity() const { return m_ID; }
    private:
        entt::entity m_ID;
        Scene *m_Scene = nullptr; // like a weak pointer 
    };
}