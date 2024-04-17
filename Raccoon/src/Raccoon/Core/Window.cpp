#include <Raccoon/Core/Window.h>

#ifdef RE_WIN32_WINDOW
    #include <Platforms/Windows/WindowsWindow.h> 
#endif

#ifdef RE_GLFW_WINDOW
    #include <Platforms/GLFW/GLFWWindow.h>
#endif

namespace Raccoon
{
    uint32_t Window::s_WindowCount = 0;

    Window* Window::Create(const WindowProperties &props)
    {
        ++s_WindowCount;
        
        #ifdef RE_WIN32_WINDOW
            return new WindowsWindow(props);
        #endif

        #ifdef RE_GLFW_WINDOW
            return new GLFWWindow(props);
        #endif
    }

    Window::~Window()
    {
        --s_WindowCount;
    }
}