#pragma once 
#include <Raccoon/Renderer/RendererAPI.h>

namespace Raccoon
{
    class RendererCommand
    {   
    public:
        static void Init();
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
        static uint32_t GetMaxTextureUnits();
        static void Clear(const glm::vec4 &color = {0.f, 0.f, 0.f, 0.f});
        static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray);
        static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count);
    private:
        static std::shared_ptr<RendererAPI> m_RendererAPI;
    };
}