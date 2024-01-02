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

    void LayerStack::PushLayer(Layer *layer)
    {   
        m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
        layer->m_Index = m_InsertIndex++;
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(Layer *overlay)
    {
        m_Layers.emplace_back(overlay);
        overlay->m_Index = m_Layers.size();
        overlay->OnAttach();
    }

    LayerStack::StackType::iterator LayerStack::PopLayer(Layer *layer)
    {
        auto end = m_Layers.begin() + m_InsertIndex;
        auto it = std::find(m_Layers.begin(), end, layer);
        auto result = m_Layers.end();
		if (it != end)
		{     
            size_t index = std::distance(m_Layers.begin(), it);
            if (m_CurrentIndex <= index)
                --m_CurrentIndex;

            layer->OnDetach();
            // for (; it != m_Layers.end(); ++it) 
            // {
            //     --((*it)->m_Index);
            // }
            m_InsertIndex--;

            result = m_Layers.erase(it);
            delete layer;
		}
        return result;
    }

    LayerStack::StackType::iterator LayerStack::PopOverlay(Layer *overlay)
    {
        auto it = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
        auto result = m_Layers.end();
		if (it != m_Layers.end())
		{
            size_t index = std::distance(m_Layers.begin(), it);
            if (m_CurrentIndex <= index)
                --m_CurrentIndex;

            overlay->OnDetach();
            // for (; it != m_Layers.end(); ++it) 
            // {
            //     --((*it)->m_Index);
            // }

            result = m_Layers.erase(it);
            delete overlay;
		}
        return result;
    }
}