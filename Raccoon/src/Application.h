#pragma once 

int main();

namespace Raccoon
{
    class Application
    {
        friend int ::main();
    public:
        Application();
        virtual ~Application();

        static Application* Get() { return s_Instance; }
    private: 
        void Run();
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}