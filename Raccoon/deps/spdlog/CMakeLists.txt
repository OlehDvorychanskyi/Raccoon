project(spdlog LANGUAGES CXX)

set(SPDLOG_SRCS src/RE_Build.cpp)

add_library(spdlog STATIC ${SPDLOG_SRCS})

target_compile_definitions(spdlog PUBLIC SPDLOG_COMPILED_LIB)
target_include_directories(spdlog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)