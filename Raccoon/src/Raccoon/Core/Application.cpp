#include <Raccoon/Core/Application.h>
#include <Raccoon/Core/Logger.h>
#include <Raccoon/Core/Assert.h>
#include <algorithm>

namespace Raccoon
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        RE_CORE_ASSERT(!s_Instance, "Application already created");
        s_Instance = this;

        auto DefaultWindow = Window::Create();
        Application::Get()->RegisterWindow(DefaultWindow, 0);
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        while (ShouldClose())
        {
            Window::ProcessInternalEvents();

            for (auto element : m_Windows)
            {
                if (!element.window->ShouldClose())
                {
                    element.window->ProcessEvents();
                    element.window->UpdateLayers(10.f);
                }
                else
                {
                    UnregisterWindow(element.window);
                    delete element.window;
                }
            }
        }
    }

    void Application::RegisterWindow(Window *window, int id)
    {
        auto idIterator = std::find_if(m_Windows.begin(), m_Windows.end(), [id](const WindowEntry& entry) 
        {
            return entry.id == id;
        });

        auto adressIterator = std::find_if(m_Windows.begin(), m_Windows.end(), [window](const WindowEntry& entry) 
        {
            return entry.window == window;
        });
    
        if (adressIterator == m_Windows.end() && idIterator == m_Windows.end())
            m_Windows.push_back({id, window});
        else
        {
            if (idIterator != m_Windows.end())
                RE_CORE_WARN("This window id is already registered");
            
            if (adressIterator != m_Windows.end())
                RE_CORE_WARN("This window is already registered");
        }
    }

    Window* Application::GetWindow(int id)
    {
        auto it = std::find_if(m_Windows.begin(), m_Windows.end(), [id](const WindowEntry& entry) 
        {
            return entry.id == id;
        });

        if (it != m_Windows.end())
            return it->window;
        else
        {
            RE_CORE_WARN("Window with id {0} could not be found", id);
            return nullptr;
        }
    }

    void Application::UnregisterWindow(Window *window)
    {
        auto it = std::find_if(m_Windows.begin(), m_Windows.end(), [window](const WindowEntry& entry) 
        {
            return entry.window == window;
        });

        if (it != m_Windows.end())
            m_Windows.erase(it);
        else
            RE_CORE_WARN("This window is not registered");
    }
} 