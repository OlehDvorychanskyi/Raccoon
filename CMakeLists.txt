cmake_minimum_required(VERSION 3.16)
project(RaccoonProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(Raccoon)

if(BUILD_TEMPLATES STREQUAL "True" OR BUILD_TEMPLATES STREQUAL "true")
    add_subdirectory(Templates)
else()
    add_subdirectory(RaccoonEditor)
endif()