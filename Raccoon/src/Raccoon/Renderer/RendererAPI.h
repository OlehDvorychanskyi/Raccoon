#pragma once 
#include <Raccoon/Renderer/VertexArray.h>
#include <glm/vec4.hpp>

namespace Raccoon
{
    class RendererAPI
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL
        };
    public:
        virtual void Init() = 0;
        virtual ~RendererAPI() = default;
        
        virtual void Clear(const glm::vec4 &color) = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetMaxTextureUnits() const = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray /*Shaders*/) = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count) = 0;
        // void DrawLines() = 0;    
        // void DrawArray() = 0;

        static std::shared_ptr<RendererAPI> Create();
        static API GetAPI() { return m_RendererAPI; }
    private:
        static API m_RendererAPI;  
    };
}