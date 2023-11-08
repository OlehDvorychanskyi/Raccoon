#include <Raccoon/Renderer/Renderer.h>
#include <Raccoon/Renderer/RendererCommand.h>

namespace Raccoon
{
    void Renderer::Init()
    {
        RendererCommand::Init();
    }

    void Renderer::Shutdown()
    {

    } 

    void Renderer::Begin(/*Env data*/)
    {

    }

    void Renderer::End()
    {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray)
    {
        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }
}