project(Raccoon LANGUAGES CXX)

set(RaccoonSources
    src/Raccoon/Core/Application.cpp
    src/Raccoon/Core/Logger.cpp
    src/Raccoon/Core/LayerStack.cpp
    src/Raccoon/Core/Window.cpp

    src/Raccoon/Events/EventQueue.cpp

    src/Raccoon/FileSystem/FileSystem.cpp
    src/Raccoon/FileSystem/FilePath.cpp

    src/Raccoon/ImGui/ImGuiLayer.cpp
    src/Raccoon/ImGui/Fonts.cpp
    src/Raccoon/ImGui/Guizmo.cpp
    
    src/Raccoon/Scene/Entity.cpp
    src/Raccoon/Scene/Scene.cpp
    src/Raccoon/Scene/Components.cpp
    src/Raccoon/Scene/SceneSerializer.cpp
    src/Raccoon/Scene/Registry.cpp
    
    src/Raccoon/Renderer/RendererContext.cpp
    src/Raccoon/Renderer/IndexBuffer.cpp
    src/Raccoon/Renderer/VertexBuffer.cpp
    src/Raccoon/Renderer/VertexArray.cpp
    src/Raccoon/Renderer/Renderer.cpp
    src/Raccoon/Renderer/RendererAPI.cpp
    src/Raccoon/Renderer/RendererCommand.cpp
    src/Raccoon/Renderer/Shaders.cpp
    src/Raccoon/Renderer/Texture2D.cpp
    src/Raccoon/Renderer/ShaderLibrary.cpp
    src/Raccoon/Renderer/Renderer2D.cpp
    src/Raccoon/Renderer/Sprite.cpp
    src/Raccoon/Renderer/ParticleSystem.cpp
    src/Raccoon/Renderer/FrameBuffer.cpp
    src/Raccoon/Renderer/Cameras.cpp
    src/Raccoon/Renderer/Color.cpp

    src/Raccoon/Math/Math.cpp
    src/Raccoon/Math/Random.cpp

    src/Raccoon/Project/Project.cpp
    src/Raccoon/Project/ProjectSerializer.cpp
)

set(WindowsSources
    src/Platforms/Windows/WindowsWindow.cpp 
    src/Platforms/Windows/WindowsInput.cpp
    src/Platforms/Windows/WindowsPlatformUtils.cpp
)   

set(OpenGLSources
    src/Platforms/OpenGL/OpenGLContext.cpp
    src/Platforms/OpenGL/OpenGLIndexBuffer.cpp
    src/Platforms/OpenGL/OpenGLVertexBuffer.cpp
    src/Platforms/OpenGL/OpenGLVertexArray.cpp
    src/Platforms/OpenGL/OpenGLRendererAPI.cpp
    src/Platforms/OpenGL/OpenGLShaders.cpp
    src/Platforms/OpenGL/OpenGLTexture2D.cpp
    src/Platforms/OpenGL/OpenGLFrameBuffer.cpp
)

add_subdirectory(deps/spdlog)
add_subdirectory(deps/glad)
add_subdirectory(deps/glfw)
add_subdirectory(deps/imgui-docking)
add_subdirectory(deps/glm/glm)
add_subdirectory(deps/stb_image)
add_subdirectory(deps/yaml-cpp)

add_library(${PROJECT_NAME} ${RaccoonSources} ${WindowsSources} ${OpenGLSources})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/deps/entt/include
)

target_precompile_headers(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Raccoon/pch.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog glad glfw imgui glm::glm_static stb_image yaml-cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(${PROJECT_NAME} 
        PUBLIC RE_DEBUG 
        # RE_NO_IMGUI   
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC RE_RELEASE
    )
endif()

if (RACCOON_TYPE STREQUAL "Game")
    target_compile_definitions(${PROJECT_NAME} PUBLIC RE_NO_IMGUI RE_OPTIMIZE)
endif()