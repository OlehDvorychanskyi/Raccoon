#include <Raccoon/Scene/Registry.h>
#include <Raccoon/Scene/Components.h>

namespace Raccoon
{
    uint32_t Registry::GetEntityIndex(entt::entity entity) const
    {
        auto it = m_Indicies.find(entity);
        if (it != m_Indicies.end()) 
            return it->second;

        return std::numeric_limits<uint32_t>::max();
    }

    void Registry::ChangeEntityPosition(entt::entity entity, uint32_t newPosition)
    {
        uint32_t currentOrder = GetEntityIndex(entity);
        std::size_t entityCount = m_Indicies.size();

        if (currentOrder != std::numeric_limits<uint32_t>::max() && newPosition < entityCount) 
        {
            bool increment = m_Indicies[entity] > newPosition;
            uint32_t oldIndex = m_Indicies[entity];
            
            for (auto it = m_Indicies.begin(); it != m_Indicies.end(); ++it) 
            {
                if (increment)
                {
                    if (it->second >= newPosition && it->second < oldIndex)
                    {
                        it->second++;
                    }
                }
                else
                { 
                    if (it->second > oldIndex && it->second <= newPosition)
                    {
                        it->second--;
                    }
                }
            }
            m_Indicies[entity] = newPosition;
            SortEntitiesByIndices();
        }
    }

    void Registry::DestroyEntity(entt::entity entity) 
    {
        m_Registry.destroy(entity);
        m_Indicies.erase(entity);
    }

    entt::entity Registry::CreateEntity()
    {
        entt::entity entity = m_Registry.create();
        m_Indicies[entity] = m_Indicies.size();

        return entity;
    }

    void Registry::SortEntitiesByIndices()
    {
        m_Registry.sort<entt::entity>([this](entt::entity a, entt::entity b)
        {
            return GetEntityIndex(a) > GetEntityIndex(b);
        });
    }
}