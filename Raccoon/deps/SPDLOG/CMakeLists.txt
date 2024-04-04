project(spdlog LANGUAGES CXX)

add_library(spdlog STATIC RE_BUILD.cpp)

target_compile_definitions(spdlog PUBLIC SPDLOG_COMPILED_LIB)
target_include_directories(spdlog PUBLIC spdlog/include)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(spdlog PRIVATE -Os)
endif()
