#pragma once 
#include <Raccoon/Renderer/RendererAPI.h>

namespace Raccoon
{
    // Maybe this class should use singleton instead "all static" 
    class RendererCommand
    {   
    public:
        static void Init();
        static void Clear(const glm::vec4 &color = {0.f, 0.f, 0.f, 0.f});
        static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray);
    private:
        static std::shared_ptr<RendererAPI> m_RendererAPI;
    };
}