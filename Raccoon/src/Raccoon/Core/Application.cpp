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

        auto DefaultWindow = Window::Create();
        Application::Get()->RegisterWindow(DefaultWindow);
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while (ShouldClose())
        {
            Window::ProcessInternalEvents();

            for (auto window : m_Windows)
            {
                if (!window->ShouldClose())
                {
                    window->ProcessEvents();
                }
                else
                {
                    UnregisterWindow(window);
                    delete window;
                }
            }
        }
    }

    void Application::RegisterWindow(Window *window)
    {
        auto it = std::find(m_Windows.begin(), m_Windows.end(), window);
        
        if (it == m_Windows.end())
            m_Windows.push_back(window);
        else
            RE_CORE_WARN("This window is already registered");
    }

    void Application::UnregisterWindow(Window *window)
    {
        auto it = std::find(m_Windows.begin(), m_Windows.end(), window);

        if (it != m_Windows.end())
            m_Windows.erase(it);
        else
            RE_CORE_WARN("This window is not registered");
    }
} 
