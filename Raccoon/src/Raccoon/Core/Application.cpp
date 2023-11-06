#include <Raccoon/Core/Application.h>

namespace Raccoon
{   
    Application* Application::m_Instance = nullptr;

    Application::Application(const ApplicationSpecification& specification)
        : m_Specification {specification}
    {
        RE_CORE_ASSERT(!m_Instance, "Application already created");
        m_Instance = this;
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