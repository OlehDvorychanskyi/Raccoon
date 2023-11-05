#pragma once 
#include <Raccoon/Core/Assert.h>

int main(int argc, char** argv);

namespace Raccoon
{
    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;  

        char* operator[] (std::size_t index)
        {
            RE_CORE_ASSERT(index < Count, "Args index should be less then args count");
            return Args[index];
        }
    };

    struct ApplicationSpecification
    {
        std::string Name = "Raccoon Application";
        ApplicationCommandLineArgs CommandLineArgs;
    };

    class Application
    { 
    public:
        Application(const ApplicationSpecification& specification);
        ~Application(); 

        static Application& Get() { return *m_Instance; }
    private: 
        static Application *m_Instance;
        ApplicationSpecification m_Specification;
        bool m_Running = true;
    private:
        void run();

    friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication(ApplicationCommandLineArgs args);
}