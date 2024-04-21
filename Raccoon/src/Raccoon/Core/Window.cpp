#include <Raccoon/Core/Window.h>
#include <Raccoon/Core/Assert.h>

#ifdef RE_WIN32_WINDOW
    #include <Platforms/Windows/WindowsWindow.h> 
#endif

#ifdef RE_GLFW_WINDOW
    #include <Platforms/GLFW/GLFWWindow.h>
#endif

namespace Raccoon
{
    uint32_t Window::s_WindowCount = 0;

    Window* Window::Create(const WindowProperties &props)
    {        
        ++s_WindowCount;

        #ifdef RE_WIN32_WINDOW
            Window *result = new WindowsWindow(props);
        #elif defined(RE_GLFW_WINDOW)
            Window *result = new GLFWWindow(props);
        #endif

        RE_CORE_ASSERT(result != nullptr, "Fail to create window");
        return result;
    }

    Window::~Window()
    {
        --s_WindowCount;
    }

    void Window::ProcessEvents()
    {
        std::shared_ptr<Event> event;
        while ((event = m_Events.GetFront()) != nullptr) 
        {   
            EventDispatcher dispatcher(*event);
            dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));
            dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(OnWindowResize));

            for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
            {
                if (!(event->Handled)) 
                {
                    (*it)->OnEvent(*event);
                }
            }
        }
    }

    void Window::UpdateLayers(float dt)
    {
        for (auto &layer : m_Layers)
            layer->OnUpdate(dt);
    }

    void Window::PushLayer(Layer *layer)
    {
        m_Layers.PushLayer(layer);
    }

    void Window::PushOverlay(Layer *overlay)
    {
        m_Layers.PushOverlay(overlay);
    }
}