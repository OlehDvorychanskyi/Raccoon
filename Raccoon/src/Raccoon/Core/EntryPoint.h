#pragma once
#include <Raccoon/Core/Application.h>
#include <Raccoon/Core/Logger.h>

Raccoon::Application* Raccoon::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    Raccoon::Logger::Init();
    
    Raccoon::Application *app = Raccoon::CreateApplication({argc, argv});
    app->Run();
    delete app;
}