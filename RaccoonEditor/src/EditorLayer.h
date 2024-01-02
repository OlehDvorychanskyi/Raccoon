#pragma once 
#include <Raccoon.h>

#include <Panels/HierarchyPanel.h>
#include <Panels/ContentBrowser.h>

namespace Raccoon
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        EditorLayer(const FilePath &projectPath);
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event &event) override;
        virtual void OnUpdate(const TimeStep &timestep) override;
        virtual void OnImGuiRender() override;
    private:
        void NewScene();
        void OpenScene();
        void OpenScene(const FilePath &path);
        void SaveScene();
        void SaveSceneAs();

        void NewProject();
        bool OpenProject();
        void OpenProject(const FilePath& path);
        void SaveProjectAs();

        void SaveSceneToActiveProject(const FilePath &path);
    private:
        ParticleSystem2D m_ParticleSystem;
        Particle2D m_Particle;

        std::shared_ptr<FrameBuffer> m_FrameBuffer;

        glm::vec2 m_ViewportSize = {0.f, 0.f};
        glm::vec2 m_ViewportPosition = {0.f, 0.f};

        std::shared_ptr<Scene> m_ActiveScene;
        FilePath m_EditorScenePath;

        // Panels 
        HierarchyPanel m_HierarchyPanel;
        ContentBrowserPanel m_ContentBrowserPanel;

        enum EditorState
        {
            Editor,
            Runtime
        };  
        EditorState m_EditorState = EditorState::Editor;

        bool m_ViewportFocused = false, m_ViewportHovered = false;

        EditorCamera m_EditorCamera;

        // Export
        bool m_ShowExportWindow = false;
        FilePath m_ExportPath;
        FilePath m_ActiveProjectPath;

        bool m_UnsavedScene = false;
    };
}