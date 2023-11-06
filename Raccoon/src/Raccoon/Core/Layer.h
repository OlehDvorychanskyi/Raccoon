#pragma once 
#include <cstdint>

namespace Raccoon
{
    class Layer
    {
    public:
        virtual void OnAttach() {}
        virtual void OnDetach() {}

        std::uint32_t GetIndex() const { return m_Index; }

        virtual ~Layer() = default;
    private:
        std::uint32_t m_Index = 0;

        friend class LayerStack;
    };
}