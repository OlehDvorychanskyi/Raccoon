project(Raccoon LANGUAGES CXX)

set(RaccoonSources
    src/Raccoon/Core/Application.cpp
)

add_library(${PROJECT_NAME} ${RaccoonSources})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} 
        PUBLIC RE_DEBUG    
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC RE_RELEASE
    )
endif()