#pragma once 
#include <Raccoon.h>
#include <memory>

class WindowsLayer : public Raccoon::Layer
{
public:
    WindowsLayer();
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Raccoon::Event &event) override;
    virtual void OnUpdate(const Raccoon::TimeStep &timestep) override;
private:
    void OpenScene(const Raccoon::FilePath &path);
private:
    std::shared_ptr<Raccoon::Scene> m_ActiveScene;
};