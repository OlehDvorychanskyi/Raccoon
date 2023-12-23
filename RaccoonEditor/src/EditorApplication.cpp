#include <Raccoon/Core/EntryPoint.h>
#include <Raccoon/Core/Application.h>

#include "EditorLayer.h"

namespace Raccoon
{
    class EditorApplication : public Application
    {
    public:
        EditorApplication(ApplicationSpecification specification)
            : Application(specification)
        {
            PushLayer(new EditorLayer);
        }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        ApplicationSpecification specification;
        specification.Name = "Editor";
        specification.CommandLineArgs = args;
        
        return new EditorApplication(specification);
    }
}