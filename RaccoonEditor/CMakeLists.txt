project(RaccoonEditor LANGUAGES CXX)

set(Sources src/EditorApplication.cpp src/EditorLayer.cpp src/Panels/HierarchyPanel.cpp src/Panels/ContentBrowser.cpp src/ProjectManagerLayer.cpp)

set(EXECUTABLE_NAME ${PROJECT_NAME})

set(Logo "${CMAKE_CURRENT_SOURCE_DIR}/../Logos/icon.o")

add_executable(${EXECUTABLE_NAME} ${Sources} ${Logo})
target_link_libraries(${EXECUTABLE_NAME} Raccoon)
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(ASSETS_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(BUILD_FOLDER ${CMAKE_BINARY_DIR})

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_FOLDER} ${BUILD_FOLDER}/bin/assets)