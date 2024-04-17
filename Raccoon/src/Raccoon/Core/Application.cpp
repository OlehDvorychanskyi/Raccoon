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
        m_SecondWindow = Window::Create({"Second Window", 400, 400});
    }

    Application::~Application()
    {
        delete m_Window; 
        delete m_SecondWindow; 
    }

    void Application::Run()
    {
        while (m_Running)
        {
            Window::ProcessInternalEvents();
            
            // m_Window->ProcessEvents();
            // m_SecondWindow->ProcessEvents();
        }
    }
} 
