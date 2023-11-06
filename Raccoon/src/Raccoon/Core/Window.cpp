#include <Raccoon/Core/Window.h>
#include <Platforms/Windows/WindowsWindow.h>

namespace Raccoon
{
    Window* Window::Create(const WindowProperties &props)
    {
        #ifdef RE_PLATFORM_WINDOWS
            return new WindowsWindow(props);
        #else   
            RE_CORE_ERROR("Couldn't create a window");
            return nullptr;
        #endif
    }
}