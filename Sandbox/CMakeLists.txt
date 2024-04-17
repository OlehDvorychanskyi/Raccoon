project(Sandbox LANGUAGES CXX)

set(SandboxSrc src/SandboxApp.cpp)

add_executable(${PROJECT_NAME} ${SandboxSrc})

target_link_libraries(${PROJECT_NAME} PUBLIC Raccoon)