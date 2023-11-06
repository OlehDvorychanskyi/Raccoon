#include "TestLayer.h"
#include <imgui.h>

void TestLayer::OnAttach() 
{   

}   

void TestLayer::OnDetach()
{

}

void TestLayer::OnEvent(Raccoon::Event &event)
{
    Raccoon::EventDispacher disp(event);
    disp.Dispatch<Raccoon::MouseMovedEvent>([] (Raccoon::MouseMovedEvent &event) {
        RE_INFO("Mouse moved: " + std::to_string(event.GetX()) + " " + std::to_string(event.GetY()));
    });
}

void TestLayer::OnUpdate()
{
    if (Raccoon::Input::IsKeyPressed(Raccoon::Key::A) == true)
    {
        RE_TRACE("A key pressed");
    }
}

void TestLayer::OnImGuiRender()
{
    ImGui::ShowDemoWindow();
}