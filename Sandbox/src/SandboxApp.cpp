#include <Raccoon/Core/EntryPoint.h>
#include <Raccoon/Core/Window.h>

class SandboxApp : public Raccoon::Application
{
public:
    SandboxApp(const std::string &name)
    {
        auto window = Raccoon::Window::Create({"User Window", 400, 400});
        Raccoon::Application::Get()->RegisterWindow(window);
    }
};

Raccoon::Application* Raccoon::CreateApplication()
{
    return new SandboxApp("Sandbox Application");
}