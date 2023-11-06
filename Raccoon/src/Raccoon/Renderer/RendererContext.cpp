#include <Raccoon/Renderer/RendererContext.h>
#include <Platforms/OpenGL/OpenGLContext.h>

namespace Raccoon
{
    std::unique_ptr<RendererContext> RendererContext::Create(void *window)
    {
        return std::make_unique<OpenGLContext>(OpenGLContext(static_cast<GLFWwindow*>(window))); // for now there is only OpenGL context
    }
}