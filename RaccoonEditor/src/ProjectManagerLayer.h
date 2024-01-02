#pragma once 
#include <Raccoon.h>
#include <Raccoon/Renderer/Color.h>
#include <vector>
#include <memory>
#include <imgui.h>

namespace Raccoon
{
    class ProjectManagerLayer : public Layer
    {
    public:
        ProjectManagerLayer();
        ~ProjectManagerLayer();
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event &event) override;
        virtual void OnUpdate(const TimeStep &timestep) override;
        virtual void OnImGuiRender() override;
    private:
        bool m_LocalProjectsSelected = true, m_AssetStoreProjectsSelected = false;
        bool m_NewProjectPopup = false;

        struct LocalProject
        {
            std::string Name;
            FilePath Path;

            bool operator== (const LocalProject &rhs)
            {
                return this->Name == rhs.Name && this->Path.GetRelativePath() == rhs.Path.GetRelativePath(); 
            } 
        };

        std::vector<LocalProject> m_LocalProjects, m_FilteredProjects;
        bool m_ShowFilteredProjects = false, m_ShowRenamePopup = false;
        LocalProject *m_SelectedProject = nullptr;
        std::shared_ptr<Texture2D> m_ProjectImage;
        ImVec2 m_WindowSize;

        Color dark{"1C1A20"}, grey{"222227"}, whiteGrey{"2E2E31"}, menu{"#16141A"};
        ImVec4 m_Dark{dark.GetRGBImGui()}, m_Grey{grey.GetRGBImGui()}, m_WhiteGrey{whiteGrey.GetRGBImGui()}, m_MenuColor{menu.GetRGBImGui()};
    
    private:
        void DrawProject(LocalProject& project);

        void SwitchToEditor();

        void SerializeProjects();
        void DeserializeProjects();
        void DrawProjectPopup(const char *title, bool modifyName = true, bool modifyPath = true);
    };
}