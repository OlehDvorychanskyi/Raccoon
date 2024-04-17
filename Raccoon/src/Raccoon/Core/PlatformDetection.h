#pragma once 
// Only pch should inlcude this file

#ifdef _WIN32
    #ifdef _WIN64
        #define RE_PLATFORM_WINDOWS
    #else
        #error "x86 build is not supported in Raccoon"
    #endif
#elif defined(__linux__)
    #define RE_PLATFORM_LINUX
    #error "Linux is not supported yet"
#elif defined(__APPLE__)
    #define RE_PLATFORM_MACOS
    #error "MacOS is not supported yet"
#else 
    #error "Couldn't detect your platform"
#endif

// #ifdef RE_PLATFORM_WINDOWS
//     #define RE_WIN32_WINDOW
// #elif RE_PLATFORM_LINUX || RE_PLATFORM_MACOS
//     #define RE_GLFW_WINDOW
// #endif

#define RE_GLFW_WINDOW