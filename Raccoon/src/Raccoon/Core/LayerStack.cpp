#include <Raccoon/Core/LayerStack.h>
#include <algorithm>

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

    void LayerStack::PushLayer(Layer* layer)
    {   
        m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
        layer->m_Index = m_InsertIndex++;
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_Layers.emplace_back(overlay);
        overlay->m_Index = m_Layers.size();
        overlay->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto end = m_Layers.begin() + m_InsertIndex;
        auto it = std::find(m_Layers.begin(), end, layer);
		if (it != end)
		{
			layer->OnDetach();
			m_Layers.erase(it);
            for (; it != m_Layers.end(); ++it) 
            {
                --((*it)->m_Index);
            }
			m_InsertIndex--;
		}
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
            for (; it != m_Layers.end(); ++it) 
            {
                --((*it)->m_Index);
            }
		}
    }
}