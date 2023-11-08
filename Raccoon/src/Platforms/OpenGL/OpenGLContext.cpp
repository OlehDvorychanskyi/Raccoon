#include <Platforms/OpenGL/OpenGLContext.h>
#include <Raccoon/Core/Assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Raccoon
{
    OpenGLContext::OpenGLContext(GLFWwindow *window)
        : m_Window {window}
    {
        RE_CORE_ASSERT(window, "Window is nullptr");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_Window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            RE_CORE_ERROR("Failed to initialize GLAD");
        else
            RE_CORE_INFO("GLAD loaded successfuly");
        
        RE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Raccoon requires OpenGL version to be at least 4.5!");
    }

    void OpenGLContext::SwapBuffer()
    {
        glfwSwapBuffers(m_Window);
    }
}