project(Raccoon LANGUAGES CXX)

set(RaccoonSources
    src/Raccoon/Core/Application.cpp
    src/Raccoon/Core/Logger.cpp
    src/Raccoon/Core/LayerStack.cpp
)

set(RaccoonHeaders
    src/Raccoon/Core/Application.h
    src/Raccoon/Core/Assert.h
    src/Raccoon/Core/Base.h
    src/Raccoon/Core/EntryPoint.h
    src/Raccoon/Core/Logger.h
    src/Raccoon/Core/PlatformDetection.h
    src/Raccoon/Core/Layer.h
    src/Raccoon/Core/LayerStack.h

    src/Raccoon/pch.h
    src/Raccoon.h
)

add_subdirectory(deps/spdlog)

add_library(${PROJECT_NAME} ${RaccoonSources} ${RaccoonHeaders})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_precompile_headers(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/Raccoon/pch.h
)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} 
        PUBLIC RE_DEBUG    
    )
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC RE_RELEASE
    )
endif()