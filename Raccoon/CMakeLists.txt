project(Raccoon LANGUAGES CXX)

set(RaccoonSources
    src/Raccoon/Core/Application.cpp
    src/Raccoon/Core/Logger.cpp
    src/Raccoon/Core/LayerStack.cpp
    src/Raccoon/Core/Window.cpp

    src/Raccoon/Events/EventQueue.cpp

    src/Raccoon/ImGui/ImGuiLayer.cpp
    
    src/Raccoon/Renderer/RendererContext.cpp
)

set(RaccoonHeaders
    src/Raccoon/Core/Application.h
    src/Raccoon/Core/Assert.h
    src/Raccoon/Core/Base.h
    src/Raccoon/Core/EntryPoint.h
    src/Raccoon/Core/Input.h
    src/Raccoon/Core/KeyCodes.h
    src/Raccoon/Core/Layer.h
    src/Raccoon/Core/LayerStack.h
    src/Raccoon/Core/Logger.h
    src/Raccoon/Core/MouseCodes.h
    src/Raccoon/Core/PlatformDetection.h
    src/Raccoon/Core/Window.h
    
    src/Raccoon/Events/Event.h
    src/Raccoon/Events/EventQueue.h
    src/Raccoon/Events/KeyEvents.h
    src/Raccoon/Events/MouseEvents.h
    src/Raccoon/Events/WindowEvents.h

    src/Raccoon/ImGui/ImGuiLayer.h

    src/Raccoon/pch.h
    src/Raccoon.h
)

set(WindowsSources
    src/Platforms/Windows/WindowsWindow.cpp 
    src/Platforms/Windows/WindowsInput.cpp
)   

set(WindowsHeaders
    src/Platforms/Windows/WindowsWindow.h
)   

set(OpenGLSources
    src/Platforms/OpenGL/OpenGLContext.cpp
)

set(OpenGLHeaders
    src/Platforms/OpenGL/OpenGLContext.h
)

add_subdirectory(deps/spdlog)
add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)
add_subdirectory(deps/imgui-docking)

add_library(${PROJECT_NAME} ${RaccoonSources} ${WindowsSources} ${OpenGLSources} ${RaccoonHeaders} ${WindowsHeaders} ${OpenGLHeaders})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_precompile_headers(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Raccoon/pch.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog glad glfw imgui)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} 
        PUBLIC RE_DEBUG    
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC RE_RELEASE
    )
endif()