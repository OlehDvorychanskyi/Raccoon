#include <Platforms/OpenGL/OpenGLContext.h>
#include <Raccoon/Core/Assert.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Raccoon
{
    void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        switch (severity) 
        {
            case GL_DEBUG_SEVERITY_HIGH: RE_CORE_CRITICAL(message);  break;
            case GL_DEBUG_SEVERITY_MEDIUM: RE_CORE_ERROR(message); break;
            case GL_DEBUG_SEVERITY_LOW: RE_CORE_WARN(message); break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: RE_CORE_INFO(message); break;
        }
    }

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
        
        // #ifdef RE_DEBUG
        //     glEnable(GL_DEBUG_OUTPUT);
        //     glDebugMessageCallback(DebugCallback, nullptr);
        // #endif
    }

    void OpenGLContext::SwapBuffer()
    {
        glfwSwapBuffers(m_Window);
    }
}