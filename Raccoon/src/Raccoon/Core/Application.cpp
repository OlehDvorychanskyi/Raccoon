#include <Raccoon/Core/Application.h>

namespace Raccoon
{   
    Application* Application::m_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification {specification}
    {
        if (m_Instance == nullptr)
            m_Instance = this;
        // else 
        //     error "Application already created"
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        while (m_Running)
        {   
            
        }
    }
}