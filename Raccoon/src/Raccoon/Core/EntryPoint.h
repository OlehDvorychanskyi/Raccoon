#pragma once
#include <Raccoon/Core/Application.h>

Raccoon::Application* Raccoon::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
    Raccoon::Application *app = Raccoon::CreateApplication({argc, argv});
    app->run();
    delete app;
}