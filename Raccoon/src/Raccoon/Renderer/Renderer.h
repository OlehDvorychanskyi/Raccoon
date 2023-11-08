#pragma once
#include <Raccoon/Renderer/RendererAPI.h>

namespace Raccoon
{
    class Renderer
    {
    public:
        static void Init();
        static void Shutdown(); 

        static void Begin(/*Env data*/);
        static void End();

        static void Submit(const std::shared_ptr<VertexArray> &vertexArray);

        static RendererAPI::API GetAPI() { return RendererAPI::API::OpenGL; } 
    private:
        // Scene data 
    };
}