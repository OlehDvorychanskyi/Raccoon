#pragma once 
#include <map>
#include <entt.hpp>

namespace Raccoon
{
    class Registry
    {
    public:
        uint32_t GetEntityIndex(entt::entity entity) const;
        void ChangeEntityPosition(entt::entity entity, uint32_t newPosition);
        void SwapEntities(entt::entity entity1, entt::entity entity2);

        void DestroyEntity(entt::entity entity);
        entt::entity CreateEntity();

        entt::registry& GetRegistry() { return m_Registry; }
    private:
        void SortEntitiesByIndices();
    private:
        entt::registry m_Registry;
        std::map<entt::entity, uint32_t> m_Indicies;
    };
}