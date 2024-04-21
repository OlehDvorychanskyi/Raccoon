project(Raccoon LANGUAGES CXX)

set(RaccoonSources 
    src/Raccoon/Core/Application.cpp
    src/Raccoon/Core/LayerStack.cpp
    src/Raccoon/Core/Logger.cpp
    src/Raccoon/Core/Window.cpp

    src/Raccoon/Events/EventQueue.cpp
)

set(WindowsSources
    src/Platforms/Windows/WindowsWindow.cpp
)

set(CrossPlatformSources
    src/Platforms/GLFW/GLFWWindow.cpp    
)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND RaccoonSources ${WindowsSources})
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND RaccoonSources ${CrossPlatformSources})
endif()

add_subdirectory(deps/SPDLOG)
add_subdirectory(deps/GLFW)

add_library(${PROJECT_NAME} STATIC ${RaccoonSources})

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog glfw)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DUNICODE)

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Raccoon/pch.h)