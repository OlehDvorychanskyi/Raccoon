#include <Raccoon/Scene/Entity.h>

namespace Raccoon
{
    Entity::Entity(entt::entity id, Scene* scene)
        : m_ID{id}, m_Scene{scene}
    {
        
    }
}