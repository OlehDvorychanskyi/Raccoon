#pragma once 
#include <Raccoon/Renderer/RendererContext.h>

struct GLFWwindow;

namespace Raccoon
{
    class OpenGLContext : public RendererContext
    {
    public:
        OpenGLContext(GLFWwindow *window);

        virtual void Init() override;
        virtual void SwapBuffer() override;
    private:
        GLFWwindow *m_Window;
    };
}