#pragma once 
#include <Application.h>
#include <Logger.h>

int main()
{
    Raccoon::Logger::Init();

    Raccoon::Application* app = Raccoon::CreateApplication();
    app->Run();
    delete app;

    return 0;
}