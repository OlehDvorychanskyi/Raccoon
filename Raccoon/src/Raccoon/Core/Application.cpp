#include <Raccoon/Core/Application.h>
#include <Raccoon/Renderer/RendererCommand.h>

#include <Raccoon/Core/TimeStep.h>

#include <Raccoon/Debug/Timer.h>

namespace Raccoon
{   
    Application* Application::m_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification {specification}
    {
        Timer timer("Initialization");
        
        RE_CORE_ASSERT(!m_Instance, "Application already created");
        m_Instance = this;

        m_Window = Window::Create({m_Specification.Name});
        m_Window->SetEventCallback([this] (std::shared_ptr<Event> event) {
            this->QueueEvent(event);
        });

        m_ImGuiLayer = new ImGuiLayer();
        m_Layers.PushOverlay(m_ImGuiLayer);

        Renderer::Init();
    } 

    Application::~Application()
    {
        delete m_Window;
        Renderer::Shutdown();
    }

    void Application::Run()
    {
        TimeStep deltaTime;
        while (m_Running)
        {
            Timer timer("Main Loop");
            deltaTime.Update();
            DispatchEvent();
            
            for (Layer *layer : m_Layers)
                layer->OnUpdate(deltaTime);

            m_ImGuiLayer->Begin();
            for (Layer *layer : m_Layers)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::QueueEvent(std::shared_ptr<Event> event)
    {
        m_Events.AddEvent(event);
    }

    void Application::DispatchEvent()
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

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::OnWindowClose(WindowCloseEvent &event)
    {
        m_Running = false;
    }

    void Application::OnWindowResize(WindowResizeEvent &event)
    {
        auto type = event.GetEventType();
        Renderer::SetViewport(event.GetWidth(), event.GetHeight());
    }

    void Application::PushLayer(Layer *layer)
    {
        m_Layers.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *overlay)
    {
        m_Layers.PushOverlay(overlay);
    }
}