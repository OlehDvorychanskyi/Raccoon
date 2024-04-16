#include <Raccoon/Core/Application.h>
#include <Raccoon/Core/Logger.h>
#include <Raccoon/Core/Assert.h>

namespace Raccoon
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        RE_CORE_ASSERT(!s_Instance, "Application already created");
        s_Instance = this;

        m_Window = Window::Create();
    }

    Application::~Application()
    {
        delete m_Window; 
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->ProcessEvents();
        }
    }
} 
