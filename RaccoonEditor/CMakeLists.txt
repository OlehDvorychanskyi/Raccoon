project(RaccoonEditor LANGUAGES CXX)

set(EditorSources 
    src/EditorApplication.cpp
    src/EditorLayer.cpp
    src/Panels/HierarchyPanel.cpp
)

add_executable(${PROJECT_NAME} ${EditorSources})

target_link_libraries(${PROJECT_NAME} Raccoon)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# target_compile_definitions(${PROJECT_NAME} PRIVATE RE_EDITOR)

# if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
#     # target_compile_options(spdlog PRIVATE -Os)
#     target_link_options(RaccoonEditor PRIVATE "-Wl,--no-keep-memory")
# endif()