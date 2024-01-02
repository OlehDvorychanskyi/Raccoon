#include <Raccoon/Core/EntryPoint.h>
#include <Raccoon/Core/Application.h>

#include "EditorLayer.h"
#include "ProjectManagerLayer.h"

namespace Raccoon
{
    class EditorApplication : public Application
    {
    public:
        EditorApplication(ApplicationSpecification specification)
            : Application(specification)
        {
            PushLayer(new ProjectManagerLayer());
        }
    };

    Application* CreateApplication(ApplicationCommandLineArgs args)
    {
        ApplicationSpecification specification;
        specification.Name = "Project Manager";
        specification.CommandLineArgs = args;
        
        return new EditorApplication(specification);
    }
}