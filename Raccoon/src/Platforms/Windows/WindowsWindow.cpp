#include <Platforms/Windows/WindowsWindow.h>
#include <Raccoon/Events/WindowEvents.h>
#include <Raccoon/Events/KeyEvents.h>
#include <Raccoon/Events/MouseEvents.h>

#include <stb_image.h>

#include <Windows.h>

enum WINDOWATTRIBUTE
{
	WA_ENABLEDARKMODE = 26,
};

struct WINCOMPATTRDATA
{
    DWORD attribute;
    PVOID pData;
    ULONG dataSize;
};

using fnSetWindowCompositionAttribute = BOOL (WINAPI *)(HWND hWnd, WINCOMPATTRDATA*);
fnSetWindowCompositionAttribute _SetWindowCompositionAttribute = reinterpret_cast<fnSetWindowCompositionAttribute>(GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute"));

namespace Raccoon
{
    uint32_t WindowsWindow::WindowCount = 0;

    WindowsWindow::WindowsWindow(const WindowProperties &props)
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProperties &props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        if (WindowCount == 0)
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        m_Window = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), 0, 0);
        ++WindowCount;

        m_Context = RendererContext::Create(m_Window);
        m_Context->Init();

        SetVSync(props.VSync);

        glfwSetWindowUserPointer(m_Window, &m_Data);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            data.Callback(std::make_shared<WindowResizeEvent>(width, height));
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData &data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Callback(std::make_shared<WindowCloseEvent>());
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Callback(std::make_shared<MouseMovedEvent>((float)xPos, (float)yPos));
		});

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Callback(std::make_shared<MouseScrolledEvent>((float)xOffset, (float)yOffset));
		});

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
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

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
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

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Callback(std::make_shared<KeyTypedEvent>(keycode));
        });
    }

    void WindowsWindow::SetLogo(const FilePath &path)
    {
        GLFWimage images[1]; 
        images[0].pixels = stbi_load(path.GetRelativePath().c_str(), &images[0].width, &images[0].height, 0, 4);
        glfwSetWindowIcon(m_Window, 1, images); 
        stbi_image_free(images[0].pixels);
    }

    void WindowsWindow::SetTitleBarDarkMode()
    {
        HWND hwnd = glfwGetWin32Window(m_Window);
    
        BOOL dark = TRUE;
        if (_SetWindowCompositionAttribute)
        {
            WINCOMPATTRDATA data = { WINDOWATTRIBUTE::WA_ENABLEDARKMODE, &dark, sizeof(dark) };
            _SetWindowCompositionAttribute(hwnd, &data);
        }
    }

    void WindowsWindow::SetVSync(bool value)
    {   
        if (value == true)
            glfwSwapInterval(1);
        else    
            glfwSwapInterval(0);
        m_Data.VSync = value;
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        --WindowCount;

        if (WindowCount == 0)
        {
            glfwTerminate();
        }
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffer();
    }
}