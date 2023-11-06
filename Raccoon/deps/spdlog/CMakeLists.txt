project(spdlog LANGUAGES CXX)

set(SPDLOG_SRCS src/RE_Build.cpp)

add_library(spdlog STATIC ${SPDLOG_SRCS})

target_compile_definitions(spdlog PUBLIC SPDLOG_COMPILED_LIB)
target_include_directories(spdlog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(spdlog PRIVATE -Os)
    target_link_options(spdlog PRIVATE "-Wl,--no-keep-memory")
endif()