project(glfw LANGUAGES C)

set(GLFWPath ${CMAKE_CURRENT_SOURCE_DIR}/glfw)

set(CommonSources  
    ${GLFWPath}/src/context.c
    ${GLFWPath}/src/init.c
    ${GLFWPath}/src/input.c
    ${GLFWPath}/src/monitor.c
    ${GLFWPath}/src/vulkan.c
    ${GLFWPath}/src/window.c

    ${GLFWPath}/src/egl_context.c
    ${GLFWPath}/src/osmesa_context.c

    ${GLFWPath}/src/platform.c
    ${GLFWPath}/src/null_init.c
    ${GLFWPath}/src/null_monitor.c
    ${GLFWPath}/src/null_window.c
    ${GLFWPath}/src/null_joystick.c
)


set(WindowsSources)
set(LinuxSources)

set(CompilerDefinitions)

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(WindowsSources 
        ${GLFWPath}/src/win32_init.c
        ${GLFWPath}/src/win32_joystick.c
        ${GLFWPath}/src/win32_monitor.c
        ${GLFWPath}/src/win32_time.c
        ${GLFWPath}/src/win32_thread.c
        ${GLFWPath}/src/win32_window.c
        ${GLFWPath}/src/win32_module.c
        ${GLFWPath}/src/wgl_context.c
    )

    set(CompilerDefinitions 
        _GLFW_WIN32
    )

elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(LinuxSources
        ${GLFWPath}/src/x11_init.c
        ${GLFWPath}/src/x11_monitor.c
        ${GLFWPath}/src/x11_window.c
        ${GLFWPath}/src/xkb_unicode.c
        ${GLFWPath}/src/posix_time.c
        ${GLFWPath}/src/posix_thread.c
        ${GLFWPath}/src/glx_context.c
        ${GLFWPath}/src/linux_joystick.c
    )

    set(CompilerDefinitions 
        _GLFW_X11
        GLFW_EXPOSE_NATIVE_WIN32
        GLFW_EXPOSE_NATIVE_WGL
    )
    
else()
    message("Could not recognize your system: ${CMAKE_HOST_SYSTEM_NAME}")   
endif()

add_library(${PROJECT_NAME} ${CommonSources} ${WindowsSources} ${LinuxSources})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${GLFWPath}/include
    PRIVATE ${GLFWPath}/src
)

target_compile_definitions(${PROJECT_NAME} PRIVATE ${CompilerDefinitions})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -Os)
    target_link_options(${PROJECT_NAME} PRIVATE "-Wl,--no-keep-memory")
endif()