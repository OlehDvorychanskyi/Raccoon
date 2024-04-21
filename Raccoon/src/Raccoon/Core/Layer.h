#pragma once 
#include <Raccoon/Events/Event.h>

namespace Raccoon
{
    class Layer
    {
    public:
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnEvent(Event &event) {}
        virtual void OnUpdate(float dt) {}
    };
}