#include <Raccoon/Core/EntryPoint.h>
#include <Raccoon/Core/Window.h>

#include "GameLayer.h"

class SandboxApp : public Raccoon::Application
{
public:
    SandboxApp(const std::string &name)
    {
        auto window = Raccoon::Window::Create({"User Window", 400, 400});
        Raccoon::Application::Get()->RegisterWindow(window, 10);

        window->PushLayer(new GameLayer);

        auto defaultWindow = Raccoon::Application::Get()->GetWindow(0); 
        defaultWindow->PushLayer(new GameLayer);
    }
};

Raccoon::Application* Raccoon::CreateApplication()
{
    return new SandboxApp("Sandbox Application");
}