#pragma once 
#include <Raccoon/Renderer/RendererAPI.h>

namespace Raccoon
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void Clear(const glm::vec4 &color) override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        virtual uint32_t GetMaxTextureUnits() const override;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count) override;
    };
}