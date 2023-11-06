#include <Raccoon/Core/EntryPoint.h>
#include <Raccoon.h>

#include "TestLayer.h"

class SandboxApplication : public Raccoon::Application
{
public:
    SandboxApplication(Raccoon::ApplicationSpecification specification)
        : Raccoon::Application(specification)
    {
        PushLayer(new TestLayer);
    }
};

Raccoon::Application* Raccoon::CreateApplication(ApplicationCommandLineArgs args)
{
    Raccoon::ApplicationSpecification specification;
    specification.Name = "Sandbox";
    specification.CommandLineArgs = args;
    
    return new SandboxApplication(specification);
}