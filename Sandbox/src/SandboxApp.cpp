#include <EntryPoint.h>
#include <iostream>

class SandboxApp : public Raccoon::Application
{
public:
    SandboxApp(const std::string &name)
    {
        std::cout << name << std::endl;
    }
};

Raccoon::Application* Raccoon::CreateApplication()
{
    return new SandboxApp("Sandbox Application");
}