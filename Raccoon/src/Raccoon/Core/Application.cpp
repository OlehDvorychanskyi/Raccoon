#include <Raccoon/Core/Application.h>
#include <Raccoon/Renderer/RendererCommand.h>
#include <Raccoon/Core/TimeStep.h>
#include <Raccoon/Debug/Timer.h>
#include <Raccoon/FileSystem/FileSystem.h>

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

        m_Window->SetLogo(FileSystem::GetAppDataPath().GetRelativePath() + "\\resources\\logo.png");
        m_Window->SetTitleBarDarkMode();
        
        #ifndef RE_NO_IMGUI
            m_ImGuiLayer = new ImGuiLayer();
            m_Layers.PushOverlay(m_ImGuiLayer);
        #endif
        
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
            #ifndef RE_OPTIMIZE
                Timer timer("Main Loop");
            #endif
            
            deltaTime.Update();
            DispatchEvent();
            
            m_Layers.BeginIterating();
            for (auto i = m_Layers.GetBeginIndex(); i < m_Layers.GetEndIndex(); i = m_Layers.GetCurrentIndex())
            {
                m_Layers.m_Layers[i]->OnUpdate(deltaTime);
            }
            m_Layers.EndIterating();


            #ifndef RE_NO_IMGUI
                m_ImGuiLayer->Begin();
            
                m_Layers.BeginIterating();
                for (auto i = m_Layers.GetBeginIndex(); i < m_Layers.GetEndIndex(); i = m_Layers.GetCurrentIndex())
                {
                    m_Layers.m_Layers[i]->OnImGuiRender();
                }
                m_Layers.EndIterating();

                m_ImGuiLayer->End();
            #endif 

            m_Window->OnUpdate();

            #ifndef RE_OPTIMIZE
                m_FrameTime = timer.GetTime();
            #endif
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
        glm::uvec2 size = m_Window->GetFramebufferSize();
        Renderer::SetViewport(size.x, size.y);

        // auto type = event.GetEventType();
        // Renderer::SetViewport(event.GetWidth(), event.GetHeight());
    }

    void Application::PushLayer(Layer *layer)
    {
        m_Layers.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *overlay)
    {
        m_Layers.PushOverlay(overlay);
    }

    void Application::PopLayer(Layer *layer)
    {
        m_Layers.PopLayer(layer);
    }

    void Application::PopOverlay(Layer *overlay)
    {
        m_Layers.PopOverlay(overlay);
    }
}