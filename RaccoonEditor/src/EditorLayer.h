#pragma once 
#include <Raccoon.h>
#include <Raccoon/Renderer/Texture2D.h>
#include <Raccoon/Renderer/Sprite.h>
#include <Raccoon/Renderer/OrthographicCameraController.h>
#include <Raccoon/Renderer/ParticleSystem.h>

#include <Raccoon/Renderer/FrameBuffer.h>

#include <Raccoon/Scene/Scene.h>
#include <Raccoon/Scene/Components.h>
#include <Raccoon/Scene/Entity.h>

#include <Raccoon/Renderer/Camera2DController.h>



class EditorLayer : public Raccoon::Layer
{
public:
    EditorLayer();
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Raccoon::Event &event) override;
    virtual void OnUpdate(const Raccoon::TimeStep &timestep) override;
    virtual void OnImGuiRender() override;
private:
    // Raccoon::OrthographicCameraController m_CameraController;
    // std::shared_ptr<Raccoon::Camera2D> m_Camera;
    // std::shared_ptr<Raccoon::Camera2DController> m_Controller;

    std::shared_ptr<Raccoon::Texture2D> m_Sprites;
    std::shared_ptr<Raccoon::Sprite> m_Grass, m_Water;
    
    std::shared_ptr<Raccoon::Texture2D> m_GrassTexture;
    std::shared_ptr<Raccoon::Texture2D> m_WaterTexture;
    std::shared_ptr<Raccoon::Texture2D> m_ChapelTexture;

    Raccoon::ParticleSystem2D m_ParticleSystem;
    Raccoon::Particle2D m_Particle;

    std::shared_ptr<Raccoon::FrameBuffer> m_FrameBuffer;

    glm::vec2 m_ViewportSize;

    Raccoon::Scene m_ActiveScene;
    // Raccoon::OrthographicCamera m_Camera;
};