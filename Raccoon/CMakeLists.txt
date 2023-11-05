project(Raccoon LANGUAGES CXX)

set(RaccoonSources
    src/Raccoon/Core/Application.cpp
    src/Raccoon/Core/Logger.cpp
)

add_subdirectory(deps/spdlog)

add_library(${PROJECT_NAME} ${RaccoonSources})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_precompile_headers(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Raccoon/pch.h
)

target_link_libraries(${PROJECT_NAME} spdlog)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} 
        PUBLIC RE_DEBUG    
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC RE_RELEASE
    )
endif()