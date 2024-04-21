#pragma once 
#include <Raccoon/Core/Layer.h>
#include <vector>

namespace Raccoon
{
    class LayerStack 
    {
        using StackType = std::vector<Layer*>;
    public:
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);

        StackType::iterator begin() { return m_Layers.begin(); }
        StackType::iterator end() { return m_Layers.end(); }
        StackType::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        StackType::reverse_iterator rend() { return m_Layers.rend(); }

        ~LayerStack();
    private:
        StackType m_Layers;
        StackType::size_type m_InsertIndex = 0;
    };
}