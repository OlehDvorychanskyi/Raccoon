#include <Raccoon/Renderer/RendererCommand.h>
#include <Raccoon/Renderer/RendererAPI.h>

namespace Raccoon
{
    std::shared_ptr<RendererAPI> RendererCommand::m_RendererAPI = RendererAPI::Create();

    void RendererCommand::Init()
    {   
        m_RendererAPI->Init();
    }

    void RendererCommand::Clear(const glm::vec4 &color)
    {
        m_RendererAPI->Clear(color);    
    }

    void RendererCommand::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
    {
        m_RendererAPI->DrawIndexed(vertexArray);
    }
}