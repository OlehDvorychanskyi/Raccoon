#include <Raccoon/Core/EntryPoint.h>
#include <Raccoon.h>

#include "WindowsLayer.h"

class TemplateApplication : public Raccoon::Application
{
public:
    TemplateApplication(Raccoon::ApplicationSpecification specification)
        : Raccoon::Application(specification)
    {
        PushLayer(new WindowsLayer);
    }
};

Raccoon::Application* Raccoon::CreateApplication(ApplicationCommandLineArgs args)
{
    Raccoon::ApplicationSpecification specification;
    Raccoon::FilePath path = args[0]; 
    specification.Name = path.GetFileNameWithoutExtention(); // executable name
    specification.CommandLineArgs = args;
    
    return new TemplateApplication(specification);
}