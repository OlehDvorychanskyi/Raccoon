#pragma once
#include <Raccoon/Renderer/RendererAPI.h>
#include <Raccoon/Renderer/Cameras.h>
#include <Raccoon/Renderer/Shaders.h>

namespace Raccoon
{
    class Renderer
    {
    public:
        static void Init();
        static void Shutdown(); 

        static void SetViewport(uint32_t width, uint32_t height);
        static uint32_t GetMaxTextureUnits();

        // static void Begin(OrthographicCamera &camera);
        // static void End();

        static void Submit(const std::shared_ptr<Shaders> &shaders, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform = glm::mat4(1.f));

        static RendererAPI::API GetAPI() { return RendererAPI::API::OpenGL; } 
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };
        
        static std::shared_ptr<SceneData> m_Data;
    };
}