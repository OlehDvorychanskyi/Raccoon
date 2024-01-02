project(glfw LANGUAGES C)

set(CommonSources  
    src/context.c
    src/init.c
    src/input.c
    src/monitor.c
    src/vulkan.c
    src/window.c
)

set(WindowsSources)
set(LinuxSources)

set(CompilerDefinitions)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(WindowsSources 
        src/win32_init.c
        src/win32_joystick.c
        src/win32_monitor.c
        src/win32_time.c
        src/win32_thread.c
        src/win32_window.c
        src/wgl_context.c
        src/egl_context.c
        src/osmesa_context.c
    )

    set(CompilerDefinitions 
        _GLFW_WIN32
    )

elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LinuxSources
        src/x11_init.c
        src/x11_monitor.c
        src/x11_window.c
        src/xkb_unicode.c
        src/posix_time.c
        src/posix_thread.c
        src/glx_context.c
        src/egl_context.c
        src/osmesa_context.c
        src/linux_joystick.c
    )

    set(CompilerDefinitions 
        _GLFW_X11
        GLFW_EXPOSE_NATIVE_WIN32
        GLFW_EXPOSE_NATIVE_WGL
    )
    
else()
    message("Could not recognize your system: ${CMAKE_SYSTEM_NAME}")   
endif()

add_library(${PROJECT_NAME} ${CommonSources} ${WindowsSources} ${LinuxSources})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(${PROJECT_NAME} PRIVATE ${CompilerDefinitions})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -Os)
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,--no-keep-memory")
endif()
