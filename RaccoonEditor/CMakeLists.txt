project(RaccoonEditor LANGUAGES CXX)

set(EditorSources 
    src/EditorApplication.cpp
    src/EditorLayer.cpp
)

add_executable(${PROJECT_NAME} ${EditorSources})

target_link_libraries(${PROJECT_NAME} Raccoon)

if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    # target_compile_options(spdlog PRIVATE -Os)
    target_link_options(spdlog PRIVATE "-Wl,--no-keep-memory")
endif()