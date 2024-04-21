#pragma once 
#include <Raccoon/Core/Window.h>
#include <vector>

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

        void RegisterWindow(Window *window, int id);
        Window* GetWindow(int id);

        static Application* Get() { return s_Instance; }
    private: 
        void Run();
        bool ShouldClose() { return m_Windows.size() > 0; }
        
        void UnregisterWindow(Window *window);
    private:
        struct WindowEntry
        {
            int id;
            Window* window;
        };
        std::vector<WindowEntry> m_Windows;

        static Application* s_Instance;
    };

    Application* CreateApplication();
}