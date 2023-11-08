#include <Platforms/OpenGL/OpenGLRendererAPI.h>

#include <glad/glad.h>

namespace Raccoon
{
    void OpenGLRendererAPI::Init() 
    {
        // init smth
    }

    void OpenGLRendererAPI::Clear(const glm::vec4 &color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) 
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}