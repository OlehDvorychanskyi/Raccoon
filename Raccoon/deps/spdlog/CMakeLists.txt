project(spdlog LANGUAGES CXX)

set(SPDLOG_SRCS src/spdlog.cpp src/stdout_sinks.cpp src/color_sinks.cpp src/file_sinks.cpp src/async.cpp src/cfg.cpp src/bundled_fmtlib_format.cpp)

add_library(spdlog STATIC ${SPDLOG_SRCS})

target_compile_definitions(spdlog PUBLIC SPDLOG_COMPILED_LIB)
target_include_directories(spdlog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)