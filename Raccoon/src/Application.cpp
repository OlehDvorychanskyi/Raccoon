#include <Application.h>
#include <Logger.h>
#include <Assert.h>

namespace Raccoon
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        if (s_Instance == nullptr)
            s_Instance = this;
        else 
        {
            // error 
        }

        RE_CORE_INFO("Info");
        RE_CORE_WARN("Warn");
        RE_CORE_ERROR("Error");

        RE_INFO("Info");
        RE_WARN("Warn");
        RE_ERROR("Error");

        RE_ASSERT(true, "Client assertion");
        RE_CORE_ASSERT(false, "Core assertion");
    }

    Application::~Application()
    {

    }

    void Application::Run()
    {
        // while (true)
        // {
        //     // std::cout << "Hello \n";
            
        // }
    }
} 
