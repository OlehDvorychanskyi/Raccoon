#include <Platforms/GLFW/GLFWWindow.h>
#include <Raccoon/Core/Assert.h>
#include <GLFW/glfw3.h>

#include <Raccoon/Events/WindowEvents.h>
#include <Raccoon/Events/KeyEvents.h>
#include <Raccoon/Events/MouseEvents.h>

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

        m_NativeWindow = glfwCreateWindow(m_Data.Props.Width, m_Data.Props.Height, m_Data.Props.Title.c_str(), 0, 0);
        RE_CORE_ASSERT(m_NativeWindow, "Fail to create a window");

        glfwSetWindowUserPointer(m_NativeWindow, &m_Data);
        InitEventCallbacks();
    }

    void GLFWWindow::InitEventCallbacks()
    {
        m_Data.Callback = [this](std::shared_ptr<Event> event)
        {
            this->m_Events.AddEvent(event);
        };

        glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height)
        {
            WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Props.Width = width;
            data.Props.Height = height;

            data.Callback(std::make_shared<WindowResizeEvent>(width, height));
        });

        glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* window)
        {
            WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Callback(std::make_shared<WindowCloseEvent>());
        });

        glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Callback(std::make_shared<MouseMovedEvent>((float)xPos, (float)yPos));
		});

        glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Callback(std::make_shared<MouseScrolledEvent>((float)xOffset, (float)yOffset));
		});

        glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
                    data.Callback(std::make_shared<KeyPressedEvent>(key));
					break;
				case GLFW_RELEASE:
					data.Callback(std::make_shared<KeyReleasedEvent>(key));
					break;
				case GLFW_REPEAT:
					data.Callback(std::make_shared<KeyPressedEvent>(key, true));
					break;
			}
		});

        glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
					data.Callback(std::make_shared<MouseButtonPressedEvent>(button));
					break;
				case GLFW_RELEASE:
					data.Callback(std::make_shared<MouseButtonReleasedEvent>(button));
					break;
			}
		});

        glfwSetCharCallback(m_NativeWindow, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Callback(std::make_shared<KeyTypedEvent>(keycode));
        });
    }

    void GLFWWindow::Shutdown()
    {
        glfwDestroyWindow(m_NativeWindow);

        if (Window::s_WindowCount == 1)
            glfwTerminate();
    }

    bool GLFWWindow::ShouldClose() const
    {
        return glfwWindowShouldClose(m_NativeWindow);
    }

    void Window::ProcessInternalEvents()
    {
        glfwPollEvents();
    }

    void GLFWWindow::SetTitle(const std::string &title) 
    {
        m_Data.Props.Title = title;

        glfwSetWindowTitle(m_NativeWindow, title.c_str());
    }

    void GLFWWindow::Resize(uint32_t width, uint32_t height) 
    {
        m_Data.Props.Width = width;
        m_Data.Props.Height = height;

        glfwSetWindowSize(m_NativeWindow, width, height);
    }

    void GLFWWindow::OnWindowClose(WindowCloseEvent &event) 
    {
        // useless cause glfw do this for us
    } 

    void GLFWWindow::OnWindowResize(WindowResizeEvent &event)
    {

    }  
}