#pragma once 
#include <Raccoon/Events/Event.h>
#include <cstdint>
#include <string>

#include <Raccoon/Core/TimeStep.h>

namespace Raccoon
{
    #ifdef RE_DEBUG
        #define DECLARE_LAYER_DEBUG() virtual std::string GetDebugName() const { return "Unknown"; }
        #define OVERRIDE_LAYER_DEBUG(name) virtual std::string GetDebugName() const override { return name; }
    #else   
        #define DECLARE_LAYER_DEBUG()
        #define OVERRIDE_LAYER_DEBUG(name)
    #endif
 
    class Layer
    {
    public:
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnEvent(Event &event) {}
        virtual void OnUpdate(const TimeStep &timestep) {}
        virtual void OnImGuiRender() {}

        std::uint32_t GetIndex() const { return m_Index; }

        virtual ~Layer() = default;

        DECLARE_LAYER_DEBUG()
    private:
        std::uint32_t m_Index = 0;

        friend class LayerStack;
    };
}