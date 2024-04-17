#include <Platforms/GLFW/GLFWWindow.h>
#include <Raccoon/Core/Assert.h>
#include <GLFW/glfw3.h>

namespace Raccoon
{
    GLFWWindow::GLFWWindow(const WindowProperties &props)
        : m_Data {props}
    {
        InitWindow();
    }

    GLFWWindow::~GLFWWindow()
    {
        Shutdown();
    }

    void GLFWWindow::InitWindow()
    {
        if (Window::s_WindowCount == 1)
            glfwInit();

        m_NativeWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), 0, 0);

        RE_CORE_ASSERT(m_NativeWindow, "Fail to create a window");
    }

    void GLFWWindow::Shutdown()
    {
        glfwDestroyWindow(m_NativeWindow);

        if (Window::s_WindowCount == 1)
            glfwTerminate();
    }

    void GLFWWindow::ProcessEvents() 
    {
        
    }

    void Window::ProcessInternalEvents()
    {
        glfwPollEvents();
    }

    void GLFWWindow::SetTitle(const std::string &title) 
    {
        m_Data.Title = title;

        glfwSetWindowTitle(m_NativeWindow, title.c_str());
    }

    void GLFWWindow::Resize(uint32_t width, uint32_t height) 
    {
        m_Data.Width = width;
        m_Data.Height = height;

        glfwSetWindowSize(m_NativeWindow, width, height);
    }
}