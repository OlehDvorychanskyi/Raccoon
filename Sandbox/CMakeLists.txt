project(Sandbox LANGUAGES CXX)

set(SandboxSrc src/SandboxApp.cpp)

add_executable(${PROJECT_NAME} ${SandboxSrc})
# add_executable(${PROJECT_NAME} WIN32 ${SandboxSrc})

target_link_libraries(${PROJECT_NAME} PUBLIC Raccoon)