#include <Raccoon/Renderer/Renderer.h>
#include <Raccoon/Renderer/RendererCommand.h>
#include <Raccoon/Renderer/Shaders.h>

#include <Raccoon/Debug/Timer.h>
#include <Raccoon/Core/Assert.h>

#include <Raccoon/Renderer/Renderer2D.h>

namespace Raccoon
{
    std::shared_ptr<Renderer::SceneData> Renderer::m_Data = std::make_shared<Renderer::SceneData>();

    void Renderer::Init()
    {
        RendererCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        Renderer2D::Shutdown();
    } 

    void Renderer::SetViewport(uint32_t width, uint32_t height)
    {
        RendererCommand::SetViewport(0, 0, width, height);
    }

    uint32_t Renderer::GetMaxTextureUnits()
    {
        return RendererCommand::GetMaxTextureUnits();
    }

    void Renderer::Begin(Camera2D &camera, const glm::mat3 &transform)
    {
        camera.OnUpdate();
        m_Data->ViewProjectionMatrix = camera.GetProjection() * glm::inverse(transform);
    }

    void Renderer::End()
    {

    }

    void Renderer::Submit(const std::shared_ptr<Shaders> &shaders, const std::shared_ptr<VertexArray> &vertexArray,  const glm::mat4 &transform)
    {
        shaders->Bind();
        shaders->SetMat4("u_Transform", transform);
        shaders->SetMat4("u_ViewProjection", m_Data->ViewProjectionMatrix);
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }
}