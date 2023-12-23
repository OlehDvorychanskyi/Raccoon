#include "EditorLayer.h"
#include <imgui.h>

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <Raccoon/Scene/SceneSerializer.h>
#include <Raccoon/Core/Input.h>
#include <Raccoon/Utils/PlatformUtils.h>

#include <filesystem>

#include <Raccoon/ImGui/Guizmo.h>

namespace Raccoon
{
    static void DisableBlendingCallback(const ImDrawList* parent_list, const ImDrawCmd* cmd) 
    {
        Raccoon::RendererCommand::SetBlending(false);
    }

    static void EnableBlendingCallback(const ImDrawList* parent_list, const ImDrawCmd* cmd) 
    {
        Raccoon::RendererCommand::SetBlending(true);
    }

    EditorLayer::EditorLayer()
    {
        
    }

    void EditorLayer::OnAttach() 
    {   
        // m_GrassTexture = Raccoon::Texture2D::Create("assets/textures/Grass.png");
        // m_WaterTexture = Raccoon::Texture2D::Create("assets/textures/Water.png");
        // m_ChapelTexture = Raccoon::Texture2D::Create("assets/textures/Chapel.png");
        // m_Sprites = Raccoon::Texture2D::Create("assets/textures/GrassSprite.png");

        // m_Grass = Raccoon::Sprite::CreateFromOffset(m_Sprites, {16.f, 16.f}, {32.f, 0.f});
        // m_Water = Raccoon::Sprite::CreateFromOffset(m_Sprites, {16.f, 16.f}, {0.f, 0.f});

        // m_Particle.BeginColor = {0.9f, 0.9f, 0.9f, 0.1f};
        // m_Particle.EndColor = {0.94f, 0.5f, 0.074f, 1.f};

        // m_Particle.BeginSize = 0.3f;
        // m_Particle.EndSize = 0.01f;

        // m_Particle.Position = {5.f, 0.f};

        // m_Particle.Velocity = {0.f, 0.2f};
        // m_Particle.VelocityRangeX = {-0.5f, 0.5f}; 
        // m_Particle.VelocityRangeY = {0.1f, 0.5f};

        Raccoon::FrameBufferSpecification spec;
        spec.Width = 1280;
        spec.Height = 720;
        m_FrameBuffer = Raccoon::FrameBuffer::Create(spec);

        RE_WARN("{0}", std::filesystem::current_path().string());

        auto commandLineArgs = Application::Get().GetSpecification().CommandLineArgs;
		if (commandLineArgs.Count > 1)
		{
			auto projectFilePath = commandLineArgs[1];
			OpenProject(projectFilePath);
		}
        else
		{
			if (!OpenProject())
				Application::Get().Close();

		}

        // auto entity1 = m_ActiveScene->CreateEntity("Chapel");
        // entity1.AddComponent<SpriteRendererComponent>();
        // entity1.GetComponent<SpriteRendererComponent>().Texture = m_ChapelTexture;
        // entity1.GetComponent<ZComponent>().ZIndex = 1;

        // auto entity2 = m_ActiveScene->CreateEntity("Rectangle");
        // entity2.AddComponent<ColorRendererComponent>();
        // entity2.GetComponent<ColorRendererComponent>().Color = glm::vec4(0.f, 0.5f, 1.f, 1.f);
        // entity2.GetComponent<Transform2DComponent>().Position = glm::vec2(0.5f, 0.5f);

        // auto camera = m_ActiveScene->CreateEntity("Camera");
        // camera.AddComponent<OrthographicCameraComponent>();
        // camera.AddComponent<EntityControllerComponent>();
        // camera.GetComponent<OrthographicCameraComponent>().Camera.SetAspectRatio(Application::Get().GetWindow().GetAspectRatio());  

        // auto testCamera = m_ActiveScene->CreateEntity("TestCamera");
        // testCamera.AddComponent<OrthographicCameraComponent>(Application::Get().GetWindow().GetAspectRatio());
        
        m_HierarchyPanel.SetScene(m_ActiveScene);

        m_EditorCamera = EditorCamera(16.f / 9.f);

        // switch (m_EditorState)
        // {
        //     case EditorState::Editor:  
        //         m_ActiveScene->OnEditorBegin();
        //         break;
        //     case EditorState::Runtime:
        //         m_ActiveScene->OnRuntimeBegin();
        //         break;
        // }

        #ifdef RE_NO_IMGUI
            m_EditorState = EditorState::Runtime;
        #else
            m_EditorState = EditorState::Editor;
        #endif

    }   

    void EditorLayer::OnDetach()
    {

    }

    void EditorLayer::OnEvent(Raccoon::Event &event)
    {
        if (m_EditorState == EditorState::Editor)
		{
			m_EditorCamera.OnEvent(event);
		}
    }

    void EditorLayer::OnUpdate(const Raccoon::TimeStep &timestep)
    {
        m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);

        // ----- Resize --------------------------------------
            FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
            if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
            {
                m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
                m_EditorCamera.SetAspectRatio((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            }
        // ---------------------------------------------------



        // m_ParticleSystem.OnUpdate(timestep);
        // m_ParticleSystem.Emit(m_Particle);

        Raccoon::Renderer2D::ResetStats();
        #ifndef RE_NO_IMGUI
            m_FrameBuffer->Bind();
        #endif
        Raccoon::RendererCommand::Clear({0.1f, 0.1f, 0.1f, 1.f});

        switch (m_EditorState)
        {
            case EditorState::Editor:
            {
                if (m_ViewportFocused)
                    m_EditorCamera.OnUpdate();
                
                m_EditorCamera.OnUpdateController(timestep, m_ViewportSize, m_ViewportPosition);
                
                m_ActiveScene->OnEditorUpdate(timestep, m_EditorCamera);
                break;
            }
            case EditorState::Runtime:
            {
                m_ActiveScene->OnRuntimeUpdate(timestep);
                break;
            }
        }
        #ifndef RE_NO_IMGUI
            m_FrameBuffer->Unbind();
        #endif
    }

    void EditorLayer::OnImGuiRender()
    {
        // ImGui::ShowDemoWindow();
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
                if (ImGui::MenuItem("New Scene", "Ctrl+N"))
                    NewScene();

                if (ImGui::MenuItem("Open Scene...", "Ctrl+O"))
                    OpenScene();

                if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                    SaveScene();
                
                if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
                    SaveSceneAs();
                
                ImGui::Separator();

                if (ImGui::MenuItem("Exit")) 
                    Application::Get().Close();

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("New Project", "Ctrl+N"))
                    NewProject();

                if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
                    OpenProject();

                if (ImGui::MenuItem("Save Project As...", "Ctrl+S"))
                    SaveProject();
            
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        m_HierarchyPanel.OnImGuiRender();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoCollapse);
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        auto viewportPosition = ImGui::GetWindowPos();
        m_ViewportPosition = {viewportPosition.x, viewportPosition.y};

        uint32_t textureID = m_FrameBuffer->GetColorAttachment();

        m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused);
        Input::BlockInputs(!m_ViewportFocused);

        ImDrawList* drawList = ImGui::GetWindowDrawList();

        drawList->AddCallback(DisableBlendingCallback, nullptr);
        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2(m_ViewportSize.x, m_ViewportSize.y), ImVec2(0, 1), ImVec2(1, 0));
        drawList->AddCallback(EnableBlendingCallback, nullptr);
        
        Entity ent = m_HierarchyPanel.GetSelectedEntity();
        if (ent)
        {
            ImVec2 windowSize = ImGui::GetWindowSize();
            Guizmo::InitWindow({m_ViewportPosition.x, m_ViewportPosition.y}, windowSize);

            Guizmo::Manipulate2D(&m_EditorCamera.GetView(), &m_EditorCamera.GetProjection(), &ent.GetComponent<Transform2DComponent>(), GuizmoMode::Move);
        }

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Editor Stats", (bool*)0, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Frame Time: %.4f ms", Application::Get().GetFrameTime());
        ImGui::Text("Draw Calls: %u", Renderer2D::GetStats().DrawCalls);

        ImGui::End();
        
        ImGui::End();
    }

    void EditorLayer::NewScene()
    {
        m_ActiveScene = std::make_shared<Scene>();
        m_HierarchyPanel.SetScene(m_ActiveScene);
    }

    void EditorLayer::OpenScene()
    {
        std::string filepath = FileDialogs::OpenFile("Raccoon Scene (*.re)\0*.re\0");
        if (!filepath.empty())  
            OpenScene(filepath);
    }

    void EditorLayer::OpenScene(const FilePath &path)
    {
        if (path.GetPath().empty())
        {
            std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
            m_HierarchyPanel.SetScene(newScene);
            m_ActiveScene = newScene;
            return;
        }

        if (path.GetFileExtention() != ".re")
        {
            RE_WARN("Could not load {0} - not a scene file", path.GetFileName());
            return;
        }

        std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
        SceneSerializer serializer(newScene);

        if (serializer.DeserializeText(path.GetRelativePath()))
        {
            m_HierarchyPanel.SetScene(newScene);
            m_ActiveScene = newScene;
            m_EditorScenePath = path;
        }
    }

    void EditorLayer::SaveScene()
    {
        if (!m_EditorScenePath.GetPath().empty())
        {
            SceneSerializer serializer(m_ActiveScene);
		    serializer.SerializeText(m_EditorScenePath);
        }
		else
			SaveSceneAs();
    }

    void EditorLayer::SaveSceneAs()
    {
        std::string filepath = FileDialogs::SaveFile("Raccoon Scene (*.re)\0*.re\0");
		if (!filepath.empty())
		{
            SceneSerializer serializer(m_ActiveScene);
		    serializer.SerializeText(filepath);
            m_EditorScenePath.SetPath(filepath);
		}
    }

    void EditorLayer::NewProject()
    {
        Project::New();
    }

    void EditorLayer::OpenProject(const FilePath& path)
    {
        if (Project::Load(path))
        {
            FilePath startScenePath = Project::GetActive()->GetConfig().StartScene;
            OpenScene(startScenePath);
        }
    }

    bool EditorLayer::OpenProject()
    {
		std::string filepath = FileDialogs::OpenFile("Raccoon Project (*.reproj)\0*.reproj\0");
		if (filepath.empty())
			return false;

		OpenProject(filepath);
		return true;
    }

    void EditorLayer::SaveProject()
    {
        auto path = FileDialogs::SaveFile("Raccoon Project (*.reproj)\0*.reproj\0");
        // Project::GetActive()->GetConfig().StartScene = m_EditorScenePath;
        Project::SaveActive(path);
    }
}