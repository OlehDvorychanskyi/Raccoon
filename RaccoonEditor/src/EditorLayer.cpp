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

#include <cstdlib>
#include <fstream>

#include <Raccoon/ImGui/Fonts.h>

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
        : Layer("EditorLayer")
    {
        
    }

    EditorLayer::EditorLayer(const FilePath &projectPath)
        : Layer("EditorLayer")
    {
        m_ActiveProjectPath = projectPath;
        OpenProject(projectPath);
    }

    void EditorLayer::OnAttach() 
    {   
        Raccoon::FrameBufferSpecification spec;
        spec.Width = 1280;
        spec.Height = 720;
        m_FrameBuffer = Raccoon::FrameBuffer::Create(spec);

        m_HierarchyPanel.SetScene(m_ActiveScene);
        m_ContentBrowserPanel.SetBasePath(m_ActiveProjectPath.GetParentPath());
        m_EditorCamera = EditorCamera(16.f / 9.f);
        m_EditorState = EditorState::Editor;
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
        // ----- Resize --------------------------------------
            FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
            if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
            {
                m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
                m_EditorCamera.SetAspectRatio((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            }
        // ---------------------------------------------------

        // Raccoon::Renderer2D::ResetStats();
        m_FrameBuffer->Bind();
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
        m_FrameBuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        // ImGui::ShowDemoWindow();
        // ImGui::ShowMetricsWindow();

        static bool p_open = true;

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar;
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
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags/*  | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoTabBar */);
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
                if (ImGui::MenuItem("Export Project"))
                {
                    m_ShowExportWindow = true;
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        m_HierarchyPanel.OnImGuiRender();
        m_ContentBrowserPanel.OnImGuiRender();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoCollapse);
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        auto viewportPosition = ImGui::GetWindowPos();
        m_ViewportPosition = {viewportPosition.x, viewportPosition.y};

        uint32_t textureID = m_FrameBuffer->GetColorAttachment();

        m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();

        bool block = !m_ViewportHovered;

        RE_CORE_INFO("Focused: {0}, Hovered: {1}, Block: {2}", m_ViewportFocused, m_ViewportHovered, block);

        Application::Get().GetImGuiLayer()->BlockEvents(block);
        Input::BlockInputs(block);

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

        // ImGui::Begin("Editor Stats", (bool*)0, ImGuiWindowFlags_NoCollapse);
        // ImGui::Text("Frame Time: %.4f ms", Application::Get().GetFrameTime());
        // ImGui::Text("Draw Calls: %u", Renderer2D::GetStats().DrawCalls);
        // ImGui::End();
        
        ImGui::End();

        if (m_ShowExportWindow)
        {
            ImGui::OpenPopup("Export Project");

            if (ImGui::BeginPopupModal("Export Project", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Export Path:");
                
                static char exportPath[256] = "";
                ImGui::InputText("##ExportPath", exportPath, IM_ARRAYSIZE(exportPath), ImGuiInputTextFlags_EnterReturnsTrue);

                ImGui::SameLine();

                if (ImGui::Button("Browse"))
                {
                    std::string filepath = FileDialogs::SaveFile("Executable (*.exe)\0*.exe\0");
                    if (!filepath.empty())
                    {
                        strcpy(exportPath, filepath.c_str());
                        m_ExportPath.SetPath(filepath);
                    }
                }

                if (ImGui::Button("Export", ImVec2(120, 0)))
                {   
                    std::string exportFolder = m_ExportPath.GetParentPath();
                    std::string executableName = m_ExportPath.GetFileNameWithoutExtention();                    

                    std::string raccoonDataFolder = FileSystem::GetAppDataPath().GetRelativePath();
                    std::string templateName = "WindowsRelease";

                    CopyFile(raccoonDataFolder + "/export/templates/" + templateName + ".exe", exportFolder + "/" + executableName + ".exe");

                    std::string scenePathFrom = Project::GetActive()->GetConfig().StartScene.GetGlobalPath();
                    
                    if (!scenePathFrom.empty())
                    {
                        std::string scenePathTo = exportFolder + "/" + executableName + ".re";
                        CopyFile(scenePathFrom, scenePathTo);
                    }
                    else 
                    {
                        RE_CORE_ERROR("There is no startup scene in your ptoject");
                    }
                
                    ImGui::CloseCurrentPopup();
                    m_ShowExportWindow = false;
                }

                ImGui::SameLine();

                if (ImGui::Button("Cancel", ImVec2(120, 0)))
                {
                    ImGui::CloseCurrentPopup();
                    m_ShowExportWindow = false;
                }

                ImGui::EndPopup();
            }
        }
    }

    void EditorLayer::NewScene()
    {
        m_ActiveScene = std::make_shared<Scene>();
        m_HierarchyPanel.SetScene(m_ActiveScene);
        m_UnsavedScene = true;
    }

    void EditorLayer::OpenScene()
    {
        std::string filepath = FileDialogs::OpenFile("Raccoon Scene (*.re)\0*.re\0");
        if (!filepath.empty())  
        {
            OpenScene(filepath);
            m_UnsavedScene = true;
        }
    }

    void EditorLayer::OpenScene(const FilePath &path)
    {
        if (path.GetPath().empty())
        {
            std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
            m_HierarchyPanel.SetScene(newScene);
            m_ActiveScene = newScene;
            m_UnsavedScene = true;
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
        m_UnsavedScene = true;
    }

    void EditorLayer::SaveScene()
    {
        if (!m_EditorScenePath.GetPath().empty())
        {
            SceneSerializer serializer(m_ActiveScene);
		    serializer.SerializeText(m_EditorScenePath);

            SaveSceneToActiveProject(m_EditorScenePath);
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

            SaveSceneToActiveProject(filepath);
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

    void EditorLayer::SaveProjectAs()
    {
        auto path = FileDialogs::SaveFile("Raccoon Project (*.reproj)\0*.reproj\0");
        // Project::GetActive()->GetConfig().StartScene = m_EditorScenePath;
        Project::SaveActive(path);
    }

    void EditorLayer::SaveSceneToActiveProject(const FilePath &path)
    {
        Project::GetActive()->GetConfig().StartScene = path;
        Project::SaveActive(m_ActiveProjectPath);
        m_UnsavedScene = false;
    }
}