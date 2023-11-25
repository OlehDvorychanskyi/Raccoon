project(stb_image LANGUAGES CXX)

set( SOURCES
    src/stb_image.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})

add_compile_definitions(${PROJECT_NAME} PRIVATE STB_IMAGE_IMPLEMENTATION)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)