#include <Raccoon/Core/LayerStack.h>

namespace Raccoon
{
    LayerStack::~LayerStack()
    {
        for (Layer *layer : m_Layers)
        {   
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer *layer)
    {   
        m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(Layer *overlay)
    {
        m_Layers.emplace_back(overlay);
        overlay->OnAttach();
    }
}