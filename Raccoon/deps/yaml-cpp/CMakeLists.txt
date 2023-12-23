project(yaml-cpp LANGUAGES C)

set(SOURCES 
    src/binary.cpp
    src/convert.cpp
    src/depthguard.cpp
    src/directives.cpp
    src/emit.cpp
    src/emitfromevents.cpp
    src/emitter.cpp
    src/emitterstate.cpp
    src/emitterutils.cpp
    src/exceptions.cpp
    src/exp.cpp
    src/memory.cpp
    src/node_data.cpp
    src/node.cpp
    src/nodebuilder.cpp
    src/nodeevents.cpp
    src/null.cpp
    src/ostream_wrapper.cpp
    src/parse.cpp
    src/parser.cpp
    src/regex_yaml.cpp
    src/scanner.cpp
    src/scanscalar.cpp
    src/scantag.cpp
    src/scantoken.cpp
    src/simplekey.cpp
    src/singledocparser.cpp
    src/stream.cpp
    src/tag.cpp
    
    src/contrib/graphbuilder.cpp
    src/contrib/graphbuilderadapter.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(${PROJECT_NAME} PUBLIC YAML_CPP_STATIC_DEFINE)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(yaml-cpp PRIVATE -Os)
    target_link_options(yaml-cpp PRIVATE "-Wl,--no-keep-memory")
endif()