project(Raccoon LANGUAGES CXX)

set(RaccoonSources 
    src/Raccoon/Core/Application.cpp
    src/Raccoon/Core/Logger.cpp
    src/Raccoon/Core/Window.cpp
)

set(WindowsSources
    src/Platforms/Windows/WindowsWindow.cpp
)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND RaccoonSources ${WindowsSources})
endif()

add_subdirectory(deps/SPDLOG)

add_library(${PROJECT_NAME} STATIC ${RaccoonSources})

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DUNICODE)

target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Raccoon/pch.h)
