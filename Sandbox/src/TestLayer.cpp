#include "TestLayer.h"
#include <imgui.h>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <Raccoon/Renderer/Renderer2D.h>

TestLayer::TestLayer()
    : m_CameraController(Raccoon::Application::Get().GetWindow().GetAspectRatio())
{
    m_GrassTexture = Raccoon::Texture2D::Create("assets/textures/Grass.png");
    m_WaterTexture = Raccoon::Texture2D::Create("assets/textures/Water.png");
    m_ChapelTexture = Raccoon::Texture2D::Create("assets/textures/Chapel.png");
}

void TestLayer::OnAttach() 
{   
    m_Sprites = Raccoon::Texture2D::Create("assets/textures/GrassSprite.png");

    // m_Grass = Raccoon::Sprite::CreateFromCoords(m_Sprites, {16.f, 16.f}, {2.f, 0.f});
    // m_Water = Raccoon::Sprite::CreateFromCoords(m_Sprites, {16.f, 16.f}, {0.f, 0.f});

    m_Grass = Raccoon::Sprite::CreateFromOffset(m_Sprites, {16.f, 16.f}, {32.f, 0.f});
    m_Water = Raccoon::Sprite::CreateFromOffset(m_Sprites, {16.f, 16.f}, {0.f, 0.f});

    m_Particle.BeginColor = {0.9f, 0.9f, 0.9f, 0.1f};
    m_Particle.EndColor = {0.94f, 0.5f, 0.074f, 1.f};

    m_Particle.BeginSize = 0.3f;
    m_Particle.EndSize = 0.01f;

    m_Particle.Position = {5.f, 0.f};

    m_Particle.Velocity = {0.f, 0.2f};
    m_Particle.VelocityRangeX = {-0.5f, 0.5f}; 
    m_Particle.VelocityRangeY = {0.1f, 0.5f};
}   

void TestLayer::OnDetach()
{

}

void TestLayer::OnEvent(Raccoon::Event &event)
{
    m_CameraController.OnEvent(event);
}

void TestLayer::OnUpdate(const Raccoon::TimeStep &timestep)
{
    m_CameraController.OnUpdate(timestep);
    RE_CORE_INFO("Camera position {0}", m_CameraController.GetCamera().GetPosition().y);

    m_ParticleSystem.OnUpdate(timestep);
    m_ParticleSystem.Emit(m_Particle);

    Raccoon::RendererCommand::Clear({0.4f, 0.4f, 0.4f, 1.f});
    Raccoon::Renderer2D::ResetStats();
    Raccoon::Renderer2D::Begin(m_CameraController.GetCamera());
    Raccoon::Renderer2D::DrawRectangle({0.f, 0.f}, {2.f, 2.f}, m_GrassTexture);
    Raccoon::Renderer2D::DrawRectangle({0.f, 0.f}, {1.f, 1.f}, m_ChapelTexture);
    Raccoon::Renderer2D::DrawRectangle({5.f, 0.f}, {1.f, 1.f}, m_Grass);
    Raccoon::Renderer2D::DrawRectangle({7.f, 0.f}, {1.f, 1.f}, m_Water);
    Raccoon::Renderer2D::DrawParticles(m_ParticleSystem);
    
    Raccoon::Renderer2D::End();
    RE_INFO("DrawCalls: {0}", Raccoon::Renderer2D::GetStats().DrawCalls);


    

    // Raccoon::Renderer2D::DrawRectangle({1.f, 1.f}, {1.f, 1.f}, glm::vec4(1.f, 1.f, 1.f, 1.f));

    // for (int i = 0; i < 1000; ++i) 
    // {
    //     for (int j = 0; j < 1000; ++j) 
    //     {
    //         float x = j * 1.f;
    //         float y = i * 1.f;
    //         // glm::vec4 color = (i + j) % 2 == 0 ? glm::vec4(1.f, 1.f, 1.f, 1.f) : glm::vec4(0.f, 0.f, 0.f, 1.f); 
            
    //         // Raccoon::Renderer2D::DrawRectangle({x, y}, {1.f, 1.f}, color);
    //         Raccoon::Renderer2D::DrawRectangle({x, y}, {1.f, 1.f}, (i + j) % 2 == 0 ? m_WaterTexture : m_GrassTexture);
    //     }
    // }
    
}

void TestLayer::OnImGuiRender()
{
    // ImGui::Begin("Texture Settings");
    // static const char* items[] = { "Smooth", "Pixelated" };
    // static int currentItem = 0;

    // if (ImGui::Combo("Texutre Quality", &currentItem, items, IM_ARRAYSIZE(items)))
    // {
    //     if (items[currentItem] == "Smooth")
    //         m_Texture->SetQuality(Raccoon::TextureQuality::Smooth);       
    //     else if (items[currentItem] == "Pixelated")
    //         m_Texture->SetQuality(Raccoon::TextureQuality::Pixelated);       
    //     else
    //         RE_CORE_ASSERT(false, "Unknown texutre quality");
    // }
    // ImGui::End();
}