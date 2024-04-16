#include <Raccoon/Core/Window.h>

#ifdef RE_PLATFORM_WINDOWS
    #include <Platforms/Windows/WindowsWindow.h>
#endif

namespace Raccoon
{
    Window* Window::Create(const WindowProperties &props)
    {
        #ifdef RE_PLATFORM_WINDOWS
            return new WindowsWindow(props);
        #else   
            #error "Raccoon only support windows window for now"
        #endif
    }
}