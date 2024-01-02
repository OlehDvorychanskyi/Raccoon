#pragma once 
#include <Raccoon/Core/Layer.h>
#include <memory>
#include <vector>

namespace Raccoon
{
    class LayerStack
    {
        using StackType = std::vector<Layer*>;
    public:
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);
        StackType::iterator PopLayer(Layer *layer);
        StackType::iterator PopOverlay(Layer *overlay);

        StackType::iterator begin() { return m_Layers.begin(); }
        StackType::iterator end() { return m_Layers.end(); }
        StackType::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        StackType::reverse_iterator rend() { return m_Layers.rend(); }
        
        void BeginIterating() { m_CurrentIndex = 0u; }
        StackType::size_type GetCurrentIndex() { return ++m_CurrentIndex; }
        StackType::size_type GetBeginIndex() { return 0u; }
        StackType::size_type GetEndIndex() { return m_Layers.size(); }
        void EndIterating() { m_CurrentIndex = 0u; }

        ~LayerStack();
    private:
        StackType m_Layers;
        StackType::size_type m_InsertIndex = 0;

        StackType::size_type m_CurrentIndex;

        friend class Application;
    };
}