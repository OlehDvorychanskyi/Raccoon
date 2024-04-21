#pragma once
#include <Raccoon/Core/Layer.h>
#include <Raccoon/Core/Logger.h>

class GameLayer : public Raccoon::Layer
{
public:
    virtual void OnEvent(Raccoon::Event &event) override 
    {

    }

    virtual void OnUpdate(float dt) override
    {
        RE_INFO("{0}", dt);
    }
};