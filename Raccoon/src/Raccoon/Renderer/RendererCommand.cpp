#include <Raccoon/Renderer/RendererCommand.h>
#include <Raccoon/Renderer/RendererAPI.h>

namespace Raccoon
{
    std::shared_ptr<RendererAPI> RendererCommand::m_RendererAPI = RendererAPI::Create();

    void RendererCommand::Init()
    {   
        m_RendererAPI->Init();
    }

    void RendererCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        m_RendererAPI->SetViewport(x, y, width, height);
    }

    uint32_t RendererCommand::GetMaxTextureUnits()
    {
        return m_RendererAPI->GetMaxTextureUnits();
    }

    void RendererCommand::Clear(const glm::vec4 &color)
    {
        m_RendererAPI->Clear(color);    
    }

    void RendererCommand::SetBlending(bool value) 
    {
        m_RendererAPI->SetBlending(value);
    }

    void RendererCommand::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
    {
        m_RendererAPI->DrawIndexed(vertexArray);
    }

    void RendererCommand::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count)
    {
        m_RendererAPI->DrawIndexed(vertexArray, count);
    }
}