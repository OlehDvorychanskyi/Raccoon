project(Templates LANGUAGES CXX)

set(Sources 
    src/Application.cpp
    src/WindowsLayer.cpp
)

set(ExecutableName "WindowsRelease")

add_executable(${ExecutableName} ${Sources})

target_link_libraries(${ExecutableName} Raccoon)