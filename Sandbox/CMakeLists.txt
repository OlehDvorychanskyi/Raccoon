project(Sandbox LANGUAGES CXX)

set(SandboxSources 
    src/SandboxApplication.cpp
    src/TestLayer.cpp
)

add_executable(${PROJECT_NAME} ${SandboxSources})

target_link_libraries(${PROJECT_NAME} Raccoon)