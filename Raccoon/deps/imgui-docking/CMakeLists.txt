project(imgui LANGUAGES CXX)

set(SOURCES 
    src/imgui_demo.cpp
    src/imgui_draw.cpp
    src/imgui_tables.cpp
    src/imgui_widgets.cpp
    src/imgui.cpp

    src/backends/imgui_impl_opengl3.cpp
    src/backends/imgui_impl_glfw.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/backends
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(imgui PRIVATE -Os)
    target_link_options(imgui PRIVATE "-Wl,--no-keep-memory")
endif()