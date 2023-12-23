#pragma once

#include <Raccoon/Scene/Entity.h>
#include <Raccoon/Core/TimeStep.h>

namespace Raccoon
{
    class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
    protected:
        virtual void OnCreate() {}
        virtual void OnUpdate(const TimeStep &timestep) {}
        virtual void OnDestroy() {}
    private:
        Entity m_Entity;

    friend class Scene;
    };
}