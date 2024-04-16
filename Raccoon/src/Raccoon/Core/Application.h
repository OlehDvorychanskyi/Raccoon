#pragma once 
#include <Raccoon/Core/Window.h>

#ifdef RE_PLATFORM_WINDOWS
    #include <Windows.h>
    int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow);
#else
    int main();
#endif

namespace Raccoon
{
    class Application
    {
        #ifdef RE_PLATFORM_WINDOWS
            friend int WINAPI ::WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow);
        #else
            friend int ::main();
        #endif
    public:
        Application();
        virtual ~Application();

        static Application* Get() { return s_Instance; }
    private: 
        void Run();
    private:
        Window *m_Window;

        bool m_Running = true;
        static Application* s_Instance;
    };

    Application* CreateApplication();
}