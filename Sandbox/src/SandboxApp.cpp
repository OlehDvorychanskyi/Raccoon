#include <Raccoon/Core/EntryPoint.h>

class SandboxApp : public Raccoon::Application
{
public:
    SandboxApp(const std::string &name)
    {
        
    }
};

Raccoon::Application* Raccoon::CreateApplication()
{
    return new SandboxApp("Sandbox Application");
}