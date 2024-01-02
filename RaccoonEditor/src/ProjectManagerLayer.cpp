#include "ProjectManagerLayer.h"
#include "EditorLayer.h"
#include <Raccoon/Utils/PlatformUtils.h>

#include <yaml-cpp/yaml.h>
#include <fstream>

namespace Raccoon
{
    ProjectManagerLayer::ProjectManagerLayer()
        : Layer("ProjectManager")
    {
        ProjectManagerLayer::DeserializeProjects();
    }
    
    ProjectManagerLayer::~ProjectManagerLayer()
    {
        ProjectManagerLayer::SerializeProjects();
    }

    void ProjectManagerLayer::OnAttach() 
    {
        m_ProjectImage = Texture2D::Create(FileSystem::GetAppDataPath().GetRelativePath() + "\\resources\\Project.png");
    }

    void ProjectManagerLayer::OnDetach() 
    {

    }

    void ProjectManagerLayer::OnEvent(Event &event) 
    {

    }

    void ProjectManagerLayer::OnUpdate(const TimeStep &timestep)
    {
        RendererCommand::Clear();
    }
    
    void ProjectManagerLayer::OnImGuiRender()
    {
        static bool p_open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = true;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(2.f, 2.f));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, m_MenuColor);
        ImGui::Begin("Project Manager", &p_open, window_flags);
        
        m_WindowSize = ImGui::GetContentRegionAvail();

        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        auto cursor = ImGui::GetCursorPos();
        cursor.x += ImGui::GetStyle().WindowPadding.x;
        cursor.y += ImGui::GetStyle().WindowPadding.y;
        ImGui::SetCursorPos(cursor);

        ImVec2 BackgroundPadding = {5.f, 5.f};
        ImGui::PushStyleColor(ImGuiCol_ChildBg, m_Grey);
        ImGui::BeginChild("BackGround", ImVec2(m_WindowSize.x - (ImGui::GetStyle().WindowPadding.x * 2.f), m_WindowSize.y - (ImGui::GetStyle().WindowPadding.y * 2.f)));
        // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
        cursor = ImGui::GetCursorPos();

        float ProjectManagerHeight = ImGui::CalcTextSize("N").y + (ImGui::GetStyle().FramePadding.y * 2.f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, m_Dark);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.f);
        ImGui::BeginChild("ProjectManagerMenu", ImVec2(ImGui::GetContentRegionAvail().x, ProjectManagerHeight));
        ImGui::PopStyleVar();
        
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
        ImGui::PushStyleColor(ImGuiCol_Button, m_Grey); 
        if (ImGui::Button("Local Projects"))
        {
            m_AssetStoreProjectsSelected = false;
            m_LocalProjectsSelected = true;
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        
        ImGui::EndChild();
        ImGui::PopStyleColor();
    
        if (m_LocalProjectsSelected)
        {
            float SearchBarHeight = ImGui::CalcTextSize("N").y + ((ImGui::GetStyle().FramePadding.y * 2.f));
            ImGui::SetCursorPos(ImVec2(cursor.x + BackgroundPadding.x, cursor.y + BackgroundPadding.y + ProjectManagerHeight));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, m_Grey);
            ImGui::BeginChild("Search Bar", ImVec2(ImGui::GetContentRegionAvail().x - BackgroundPadding.x, SearchBarHeight));
            
            ImGui::BeginGroup();

            if (ImGui::Button("New Project"))
            {
                m_NewProjectPopup = true;
            }

            ImGui::SameLine();

            if (ImGui::Button("Import Project"))
            {
                auto path = FileDialogs::OpenFile("Raccoon Project (*.reproj)\0*.reproj\0");
                if (!path.empty())
                {
                    FilePath Path = path;
                    m_LocalProjects.push_back({Path.GetFileNameWithoutExtention(), Path.GetParentPath()});
                }
            }

            ImGui::SameLine();

            static char m_SearchQuery[300];
            float searchBarWidth = ImGui::GetContentRegionAvail().x * 0.8f;
            ImGui::PushItemWidth(searchBarWidth);
            if (ImGui::InputTextWithHint("##Search Project", "Filter Projects", m_SearchQuery, sizeof(m_SearchQuery)))
            {
                if (m_SearchQuery[0] =='\0')
                    m_ShowFilteredProjects = false;
                else
                    m_ShowFilteredProjects = true;   
                
                m_FilteredProjects.clear();
                for (const auto& project : m_LocalProjects)
                {
                    if (project.Name.find(m_SearchQuery) != std::string::npos)
                    {
                        m_FilteredProjects.push_back(project);
                    }
                }
            }
            ImGui::PopItemWidth();

            ImGui::EndGroup();

            ImGui::EndChild();
            ImGui::PopStyleColor();
            
            ImGui::PushStyleColor(ImGuiCol_ChildBg, m_Dark);
            ImGui::SetCursorPosX(cursor.x + BackgroundPadding.x);
            ImGui::BeginChild("Project list", ImVec2(ImGui::GetContentRegionAvail().x - 150.f - BackgroundPadding.x, ImGui::GetContentRegionAvail().y - BackgroundPadding.y));
            
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(m_Dark.x + 0.1f, m_Dark.y + 0.1f, m_Dark.z + 0.1f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(m_Dark.x + 0.05f, m_Dark.y + 0.05f, m_Dark.z + 0.05f, 1.f));
            ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(m_Dark.x + 0.05f, m_Dark.y + 0.05f, m_Dark.z + 0.05f, 1.f));


            if (!m_ShowFilteredProjects)
            {
                for (auto &project : m_LocalProjects)
                {
                    DrawProject(project);
                }
            }
            else
            {
                for (auto &project : m_FilteredProjects)
                {
                    DrawProject(project);
                }
            }

            ImGui::PopStyleColor(3);  

            ImGui::EndChild();
            ImGui::PopStyleColor();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, ImGui::GetStyle().ItemSpacing.y));
            ImGui::SameLine();
            ImGui::PopStyleVar();

            ImGui::PushStyleColor(ImGuiCol_ChildBg, m_Grey);
            ImGui::BeginChild("EditProject", ImVec2(150.f, ImGui::GetContentRegionAvail().y - BackgroundPadding.y));
            float buttonWidth = ImGui::GetContentRegionAvail().x - BackgroundPadding.x; 
            ImVec2 buttonSize = ImVec2(buttonWidth, 0.f);

            // ImGui::SetCursorPosX(ImGui::GetCursorPosX() + BackgroundPadding.x);
            // ImGui::SetCursorPosY(ImGui::GetCursorPosY() + BackgroundPadding.y);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().ItemSpacing.x);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().ItemSpacing.y);
            ImGui::BeginGroup();
            if (ImGui::Button("Edit", buttonSize))
            {
                if (m_SelectedProject)
                {
                    SwitchToEditor();
                    ImGui::PopStyleColor(3);
                    ImGui::PopStyleVar();
                    ImGui::EndGroup();
                    ImGui::EndChild();
                    ImGui::EndChild();
                    ImGui::End();
                    return;
                }
            }
            
            if (ImGui::Button("Run", buttonSize))
            {
                // ToDo: run final project like a final executable
            }
            
            if (ImGui::Button("Rename", buttonSize))
            {
                m_ShowRenamePopup = true;
            }
            
            if (ImGui::Button("Remove", buttonSize))
            {
                if (m_SelectedProject)
                {
                    for (auto i = m_LocalProjects.begin(); i != m_LocalProjects.end(); ++i)
                    {
                        if (*i == *m_SelectedProject)
                        {
                            m_LocalProjects.erase(i);
                            break;
                        }
                    }
                }
            }
            ImGui::EndGroup();
            ImGui::EndChild();
            ImGui::PopStyleColor();
            // ImGui::PopStyleVar();

            ImGui::EndChild();
            ImGui::PopStyleColor();        
    
            if (m_NewProjectPopup)
            {
                ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));
                ImGui::OpenPopup("New Project");
                
                if (ImGui::BeginPopupModal("New Project", NULL, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    ImGui::Text("Project Name:");
                    static char name[256] = "New Project";
                    ImGui::InputText("##ProjectName", name, sizeof(name));

                    ImGui::Text("Project Path:");
                    static char path[256] = "C:\\";
                    ImGui::InputText("##ProjectPath", path, sizeof(path));
                    ImGui::SameLine();
                    
                    if (ImGui::Button("Browse"))
                    {
                        auto folder = FileDialogs::OpenFolder();
                        if (!folder.empty())
                        {
                            // check whether in this path is other projects 
                            strcpy(path, folder.c_str());
                        }
                    }

                    if (!FilePath(path).IsEmptyFolder())
                    {
                        ImGui::TextColored({1.f, 1.f, 0.f, 1.f}, "You can create project only in empty folder");
                    }

                    ImVec2 textSize = ImGui::CalcTextSize("Create");

                    float width = ImGui::GetWindowSize().x;
                    float offset = width / 4.f;
                    
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);

                    ImGui::SetCursorPosX(offset - (textSize.x / 2.f));

                    if (ImGui::Button("Create"))
                    {
                        if (FilePath(path).IsEmptyFolder())
                        {
                            m_LocalProjects.push_back({name, path});
                            std::shared_ptr<Project> project = Project::New();

                            project->GetConfig().Name = name;
                            project->GetConfig().AssetDirectory = std::string(path) + "/assets";

                            Project::SaveActive(path);

                            ImGui::CloseCurrentPopup();
                            m_NewProjectPopup = false;
                        }
                        else
                            RE_CORE_ERROR("{0} isn't empty", path);
                    }

                    ImGui::SameLine();

                    textSize = ImGui::CalcTextSize("Cancel");

                    ImGui::SetCursorPosX(width - offset - ((textSize.x / 2.f)));

                    if (ImGui::Button("Cancel"))
                    {
                        ImGui::CloseCurrentPopup();
                        m_NewProjectPopup = false;
                    }

                    ImGui::EndPopup();
                }
                ImGui::PopStyleVar();
            }

            if (m_ShowRenamePopup)
            {
                ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));
                ImGui::OpenPopup("Rename Project");
                
                if (ImGui::BeginPopupModal("Rename Project", NULL, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    ImGui::Text("Project Name:");
                    static char name[256];
                    static bool isInitialized = false;

                    if (!isInitialized)
                    {
                        std::strncpy(name, m_SelectedProject->Name.c_str(), sizeof(name) - 1);
                        name[sizeof(name) - 1] = '\0'; 
                        isInitialized = true;
                    }

                    ImGui::InputText("##ProjectName", name, sizeof(name));

                    ImGui::Text("Project Path:");
                    
                    static std::string projectPathBuffer = m_SelectedProject->Path.GetRelativePath();
                    static char* projectPathEditable = &projectPathBuffer[0];

                    ImGui::InputText("##ProjectPath", projectPathEditable, projectPathBuffer.size(), ImGuiInputTextFlags_ReadOnly);
                    
                    ImVec2 textSize = ImGui::CalcTextSize("Rename");

                    float width = ImGui::GetWindowSize().x;
                    float offset = width / 4.f;
                    
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.f);

                    ImGui::SetCursorPosX(offset - (textSize.x / 2.f));

                    if (ImGui::Button("Rename"))
                    {
                        std::filesystem::rename(m_SelectedProject->Path.GetRelativePath() + "\\" + m_SelectedProject->Name + ".reproj", m_SelectedProject->Path.GetRelativePath() + std::string("\\") + name + std::string(".reproj"));
                        m_SelectedProject->Name = name;

                        isInitialized = false;
                        ImGui::CloseCurrentPopup();
                        m_ShowRenamePopup = false;
                    }

                    ImGui::SameLine();

                    textSize = ImGui::CalcTextSize("Cancel");

                    ImGui::SetCursorPosX(width - offset - ((textSize.x / 2.f)));

                    if (ImGui::Button("Cancel"))
                    {
                        isInitialized = false;
                        ImGui::CloseCurrentPopup();
                        m_ShowRenamePopup = false;
                    }

                    ImGui::EndPopup();
                }
                ImGui::PopStyleVar();
            }
        }
        else if (m_AssetStoreProjectsSelected)
        {

        }

        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }

    void ProjectManagerLayer::DrawProject(LocalProject& project) 
    {
        std::string uniqueId = project.Name + project.Path.GetGlobalPath();

        ImGui::PushID(uniqueId.c_str());

        bool selected = false;
        if (m_SelectedProject)
            selected = project == *m_SelectedProject;

        auto CursorPosition = ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY());  
        CursorPosition.x += ImGui::GetStyle().ItemSpacing.x;
        CursorPosition.y += ImGui::GetStyle().ItemSpacing.y;
        ImGui::SetCursorPosX(CursorPosition.x);
        ImGui::SetCursorPosY(CursorPosition.y);
        
        // ImGui::Selectable(("##" + uniqueId).c_str(), selected, 0,  ImVec2(ImGui::GetContentRegionAvail().x - 10.f, 74.f));
        float selectableHeight = 64.f;
        ImGui::Selectable(("##" + uniqueId).c_str(), selected, 0, ImVec2(ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x, selectableHeight));

        if (ImGui::IsItemClicked())
        {
            m_SelectedProject = &project;
        }

        // ImGui::SetCursorPosX(CursorPosition.x + 15.0f);
        // ImGui::SetCursorPosY(CursorPosition.y + 10.0f);
        ImGui::SetCursorPosX(CursorPosition.x);
        ImGui::SetCursorPosY(CursorPosition.y);
        ImGui::Image(reinterpret_cast<void*>(m_ProjectImage->GetRendererID()), ImVec2(64.f, 64.f), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::Text("%s", project.Name.c_str());

        CursorPosition = ImVec2(ImGui::GetCursorPosX(), ImGui::GetCursorPosY());

        ImGui::SetCursorPosX(CursorPosition.x);
        ImGui::SetCursorPosY(CursorPosition.y + 10.0f);

        ImGui::Text("%s", project.Path.GetGlobalPath().c_str());
        ImGui::EndGroup();

        // ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);
        ImGui::PopID();
    }

    void ProjectManagerLayer::SwitchToEditor()
    {
        if (m_SelectedProject)
        {
            Application::Get().GetWindow().SetTitle("Raccoon Editor");

            if (m_SelectedProject->Path.IsDirectory())
                Application::Get().PushLayer(new EditorLayer(m_SelectedProject->Path.GetRelativePath() + "\\" + m_SelectedProject->Name + ".reproj"));
            else
                Application::Get().PushLayer(new EditorLayer(m_SelectedProject->Path.GetRelativePath()));  

            Application::Get().PopLayer(this);  
            // m_LocalProjectsSelected = false;
        }
    }

    void ProjectManagerLayer::SerializeProjects()
    {
        YAML::Emitter out;
        out << YAML::BeginSeq;

        for (const auto& project : m_LocalProjects) 
        {
            out << YAML::BeginMap;
            out << YAML::Key << "Name" << YAML::Value << project.Name;
            out << YAML::Key << "Path" << YAML::Value << project.Path.GetRelativePath();
            out << YAML::EndMap;
        }

        out << YAML::EndSeq;
        std::string filename = FileSystem::GetAppDataPath().GetRelativePath() + "\\recent_projects.ini";
        std::ofstream fout(filename);
        fout << out.c_str();
    }

    void ProjectManagerLayer::DeserializeProjects()
    {
        try 
        {
            std::string filename = FileSystem::GetAppDataPath().GetRelativePath() + "\\recent_projects.ini";
            std::ifstream fin(filename);
            if (fin.good())
            {
                fin.close();
                YAML::Node root = YAML::LoadFile(filename);

                for (const auto& node : root) 
                {
                    LocalProject project;
                    project.Name = node["Name"].as<std::string>();
                    project.Path = node["Path"].as<std::string>();
                    m_LocalProjects.push_back(project);
                }
            }
        } 
        catch (const YAML::Exception& e) 
        {
            RE_CORE_ERROR("Error while deserializing YAML: {0}", e.what());
        }
    }
}