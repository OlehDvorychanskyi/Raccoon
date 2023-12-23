#pragma once 
#include <Raccoon.h>

#include <Panels/HierarchyPanel.h>

namespace Raccoon
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
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
        void SaveProject();
    private:
        // Raccoon::OrthographicCameraController m_CameraController;
        // std::shared_ptr<Raccoon::Camera2D> m_Camera;
        // std::shared_ptr<Raccoon::Camera2DController> m_Controller;

        std::shared_ptr<Texture2D> m_Sprites;
        std::shared_ptr<Sprite> m_Grass, m_Water;
        
        std::shared_ptr<Texture2D> m_GrassTexture;
        std::shared_ptr<Texture2D> m_WaterTexture;
        std::shared_ptr<Texture2D> m_ChapelTexture;

        ParticleSystem2D m_ParticleSystem;
        Particle2D m_Particle;

        std::shared_ptr<FrameBuffer> m_FrameBuffer;

        glm::vec2 m_ViewportSize = {0.f, 0.f};
        glm::vec2 m_ViewportPosition = {0.f, 0.f};
        // Raccoon::OrthographicCamera m_Camera;

        std::shared_ptr<Scene> m_ActiveScene;
        FilePath m_EditorScenePath;

        // Panels 
        HierarchyPanel m_HierarchyPanel;

        enum EditorState
        {
            Editor,
            Runtime
        };  
        EditorState m_EditorState = EditorState::Editor;

        bool m_ViewportFocused = false, m_ViewportHovered = false;

        EditorCamera m_EditorCamera;
    };
}