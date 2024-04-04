project(Raccoon LANGUAGES CXX)

set(RaccoonSrc 
    src/Application.cpp
    src/Logger.cpp
)

add_subdirectory(deps/SPDLOG)

add_library(RaccoonLibrary STATIC ${RaccoonSrc})

target_link_libraries(RaccoonLibrary PUBLIC spdlog)

target_include_directories(RaccoonLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)