#pragma once 
#include <Raccoon/Core/Application.h>
#include <Raccoon/Core/Logger.h>

#ifdef RE_PLATFORM_WINDOWS
    #include <Windows.h>

    int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
    {
        Raccoon::Logger::Init();

        Raccoon::Application* app = Raccoon::CreateApplication();
        app->Run();
        delete app;

        return 0;
    }
#else
    #ifdef RE_PLATFORM_LINUX || RE_PLATFORM_MACOS
        int main()
        {
            Raccoon::Logger::Init();

            Raccoon::Application* app = Raccoon::CreateApplication();
            app->Run();
            delete app;

            return 0;
        }
    #endif
#endif