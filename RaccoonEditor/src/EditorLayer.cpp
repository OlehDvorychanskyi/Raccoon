#include "EditorLayer.h"
#include <imgui.h>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <Raccoon/Renderer/Renderer2D.h>
#include <Raccoon/Renderer/RendererCommand.h>

#include <Raccoon/Scene/Components.h>


void DisableBlendingCallback(const ImDrawList* parent_list, const ImDrawCmd* cmd) 
{
    Raccoon::RendererCommand::SetBlending(false);
}

void EnableBlendingCallback(const ImDrawList* parent_list, const ImDrawCmd* cmd) 
{
    Raccoon::RendererCommand::SetBlending(true);
}

EditorLayer::EditorLayer()
    // : m_CameraController(Raccoon::Application::Get().GetWindow().GetAspectRatio())
{
    m_GrassTexture = Raccoon::Texture2D::Create("assets/textures/Grass.png");
    m_WaterTexture = Raccoon::Texture2D::Create("assets/textures/Water.png");
    m_ChapelTexture = Raccoon::Texture2D::Create("assets/textures/Chapel.png");
}

void EditorLayer::OnAttach() 
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
    
    Raccoon::FrameBufferSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    m_FrameBuffer = Raccoon::FrameBuffer::Create(spec);

    auto entity1 = m_ActiveScene.CreateEntity();
    entity1.AddComponent<Raccoon::SpriteRendererComponent>();
    entity1.GetComponent<Raccoon::SpriteRendererComponent>().Texture = m_ChapelTexture;
    entity1.GetComponent<Raccoon::ZComponent>().ZIndex = 1;

    auto entity2 = m_ActiveScene.CreateEntity();
    entity2.AddComponent<Raccoon::ColorRendererComponent>();
    entity2.GetComponent<Raccoon::ColorRendererComponent>().Color = glm::vec4(0.f, 0.5f, 1.f, 1.f);
    entity2.GetComponent<Raccoon::Transform2DComponent>().Translation = glm::vec2(0.5f, 0.5f);

    auto entity3 = m_ActiveScene.CreateEntity();
    entity3.AddComponent<Raccoon::OrthographicCameraComponent>();
    entity3.GetComponent<Raccoon::OrthographicCameraComponent>().Camera.SetAspectRatio(Raccoon::Application::Get().GetWindow().GetAspectRatio());
    // entity3.GetComponent<Raccoon::OrthographicCameraComponent>().Camera.FixedAspectRatio = true;


    // m_Camera = std::make_shared<Raccoon::Camera2D>();
    // m_Camera->SetAspectRatio(1280, 720);

    // m_Controller = std::make_shared<Raccoon::Camera2DController>(m_Camera);

    // m_Camera.SetAspectRatio();
}   

void EditorLayer::OnDetach()
{

}

void EditorLayer::OnEvent(Raccoon::Event &event)
{
    // m_CameraController.OnEvent(event);
    // m_Controller->OnEvent(event);
}

void EditorLayer::OnUpdate(const Raccoon::TimeStep &timestep)
{
    // m_CameraController.OnUpdate(timestep);
    // m_Controller->OnUpdate(timestep);

    m_ParticleSystem.OnUpdate(timestep);
    m_ParticleSystem.Emit(m_Particle);

    m_FrameBuffer->Bind();
    Raccoon::RendererCommand::Clear({0.4f, 0.4f, 0.4f, 1.f});
    Raccoon::Renderer2D::ResetStats();
    // Raccoon::Renderer2D::Begin(m_CameraController.GetCamera());
    // Raccoon::Renderer2D::Begin(*m_Controller->GetCamera());
    m_ActiveScene.OnUpdate(timestep);
    // Raccoon::Renderer2D::End();

    m_FrameBuffer->Unbind();
    RE_INFO("DrawCalls: {0}", Raccoon::Renderer2D::GetStats().DrawCalls);
}



void EditorLayer::OnImGuiRender()
{
    static bool p_open = true;

    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }
        
    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit")) 
                Raccoon::Application::Get().Close();

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Viewport");
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    if (m_ViewportSize != *((glm::vec2*)&viewportSize))
    {
        m_ViewportSize.x = viewportSize.x;
        m_ViewportSize.y = viewportSize.y;
        m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
    }
    uint32_t textureID = m_FrameBuffer->GetColorAttachment();

    ImDrawList* drawList = ImGui::GetWindowDrawList();

    drawList->AddCallback(DisableBlendingCallback, nullptr);
    ImGui::Image((void*)textureID, ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
    drawList->AddCallback(EnableBlendingCallback, nullptr);

    ImGui::End();
    ImGui::PopStyleVar();
    
    ImGui::End();
}