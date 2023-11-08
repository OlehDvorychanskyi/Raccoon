#include <Raccoon/Core/Application.h>
#include <Raccoon/Renderer/RendererCommand.h>

namespace Raccoon
{   
    Application* Application::m_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification {specification}
    {
        RE_CORE_ASSERT(!m_Instance, "Application already created");
        m_Instance = this;

        m_Window = Window::Create({m_Specification.Name});
        m_Window->SetEventCallback([this] (std::shared_ptr<Event> event) {
            this->QueueEvent(event);
        });

        m_ImGuiLayer = new ImGuiLayer();
        m_Layers.PushOverlay(m_ImGuiLayer);

        Renderer::Init();

        uint32_t arr[] =
        {
            0, 1, 2
        };

        float pos[] =
        {
            -0.5f, -0.5f, 0.f,
            0.f, 0.5f, 0.f, 
            0.5f, -0.5f, 0.f 
        };

        BufferLayout layout = {{ShaderDataType::Float3, "pos"}};

        std::shared_ptr<IndexBuffer> ib = IndexBuffer::Create(arr, 3);

        std::shared_ptr<VertexBuffer> vb = VertexBuffer::Create(pos, sizeof(pos));
        vb->SetLayout(layout);

        m_VertexArray = VertexArray::Create();
        m_VertexArray->SetIndexBuffer(ib);
        m_VertexArray->AddVertexBuffer(vb);

        m_Shaders = Shaders::Create("Vertex.txt", "Fragment.txt");
    }

    Application::~Application()
    {
        delete m_Window;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            DispatchEvent();

            for (Layer *layer : m_Layers)
                layer->OnUpdate();

            RendererCommand::Clear({0.1f, 0.1f, 0.1f, 1.f});
            
            Renderer::Begin();
            m_Shaders->Bind();
            Renderer::Submit(m_VertexArray);
            Renderer::End();
            
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
            RE_CORE_INFO(event->ToString());

            EventDispacher dispatcher(*event);
            dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Close));
            dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(OnWindowResize));

            for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
            {
                if (!(event->Handled)) 
                {
                    #ifdef RE_DEBUG
                        RE_CORE_INFO((*it)->GetDebugName());
                    #endif
                    (*it)->OnEvent(*event);
                }
            }
        }
    }

    void Application::Close(WindowCloseEvent &event)
    {
        RE_CORE_INFO("Window closed");
        m_Running = false;
    }

    void Application::OnWindowResize(WindowResizeEvent &event)
    {
        RE_CORE_INFO("Window resized");
        auto type = event.GetEventType();
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