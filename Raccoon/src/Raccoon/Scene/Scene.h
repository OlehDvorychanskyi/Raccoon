#pragma once
#include <Raccoon/Core/TimeStep.h>
#include <Raccoon/Events/Event.h>
#include <entt.hpp> 

namespace Raccoon
{
    class Entity;

    class Scene 
    {
    public:
        Scene();
        ~Scene();

        void OnUpdate(const TimeStep &timestep);
        
        Entity CreateEntity(const std::string& name = std::string());

        template<typename T>
		void OnComponentAdded(Entity entity, T& component);
    private:
        entt::registry m_Registry;

        friend class Entity;
    };
}