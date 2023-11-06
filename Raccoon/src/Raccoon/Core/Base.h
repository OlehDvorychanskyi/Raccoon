#pragma once

#define BIT(x) (1 << x) 

#define RE_EXPAND_MACRO(x) x
#define RE_STRINGIFY_MACRO(x) #x

#define BIND_EVENT_FUNCTION(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#ifdef RE_DEBUG
    #ifdef RE_PLATFORM_WINDOWS
        #define RE_DEBUGBREAK() __debugbreak();
    #else
        #error "Debugbreak doesn't supported for your platform yet"
    #endif
    #define RE_ENABLE_ASSERTS
#else
    #ifndef RE_RELEASE
        #define RE_RELEASE
    #endif
    #define RE_DEBUGBREAK()
#endif

#ifdef RE_PLATFORM_WINDOWS || RE_PLATFORM_LINUX || RE_PLATFORM_MACOS
    #define RE_GLFW
#else
    #error "Raccoon only support GLFW for window creation now"
#endif