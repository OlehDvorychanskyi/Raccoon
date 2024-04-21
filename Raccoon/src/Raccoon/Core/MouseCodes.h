#pragma once 
#include <cstdint>

namespace Raccoon
{
    using MouseCode = int16_t;
    
    namespace Mouse
    {
        enum : MouseCode
        {
            #ifdef RE_GLFW_WINDOW
                ButtonLeft             = 0,
                ButtonRight            = 1,
                ButtonMiddle           = 2

            #elif defined(RE_WIN32_WINDOW)
                ButtonLeft = VK_LBUTTON,
                ButtonRight = VK_RBUTTON,
                ButtonMiddle = VK_MBUTTON,
            #endif
        };
    }
}