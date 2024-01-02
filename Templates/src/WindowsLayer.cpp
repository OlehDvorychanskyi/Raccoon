#include "WindowsLayer.h"

WindowsLayer::WindowsLayer()
{
    // TODO: Create .pck file 
    std::string executableName = Raccoon::Application::Get().GetSpecification().Name;
    RE_CORE_INFO("{0}", executableName);
    OpenScene(executableName + ".re");
}

void WindowsLayer::OnAttach() 
{
    
}

void WindowsLayer::OnDetach()
{

}

void WindowsLayer::OnEvent(Raccoon::Event &event) 
{

}

void WindowsLayer::OnUpdate(const Raccoon::TimeStep &timestep) 
{   
    m_ActiveScene->OnViewportResize(Raccoon::Application::Get().GetWindow().GetWidth(), Raccoon::Application::Get().GetWindow().GetHeight());

    Raccoon::RendererCommand::Clear({0.1f, 0.1f, 0.1f, 1.f});
    m_ActiveScene->OnRuntimeUpdate(timestep);
}

void WindowsLayer::OpenScene(const Raccoon::FilePath &path)
{
    std::shared_ptr<Raccoon::Scene> newScene = std::make_shared<Raccoon::Scene>();
    Raccoon::SceneSerializer serializer(newScene);

    if (serializer.DeserializeText(path.GetRelativePath()))
    {
        m_ActiveScene = newScene;
    }
}
