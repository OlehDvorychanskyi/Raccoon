#pragma once 
#include <Raccoon.h>

class TestLayer : public Raccoon::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Raccoon::Event &event) override;
    virtual void OnUpdate() override;
    virtual void OnImGuiRender() override;
};
