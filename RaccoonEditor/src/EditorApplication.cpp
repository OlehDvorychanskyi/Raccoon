#include <Raccoon/Core/EntryPoint.h>
#include <Raccoon.h>

#include "EditorLayer.h"

class EditorApplication : public Raccoon::Application
{
public:
    EditorApplication(Raccoon::ApplicationSpecification specification)
        : Raccoon::Application(specification)
    {
        PushLayer(new EditorLayer);
    }
};

Raccoon::Application* Raccoon::CreateApplication(ApplicationCommandLineArgs args)
{
    Raccoon::ApplicationSpecification specification;
    specification.Name = "Editor";
    specification.CommandLineArgs = args;
    
    return new EditorApplication(specification);
}