#pragma once 
#include <Raccoon/Renderer/RendererAPI.h>

namespace Raccoon
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void Clear(const glm::vec4 &color) override;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
    };
}