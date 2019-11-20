cmake_minimum_required(VERSION 3.10)

project(parser LANGUAGES CXX)

set(PARSER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(PARSER
    ${PARSER_SOURCES}/SpriteFile.cpp
    ${PARSER_SOURCES}/SpriteChild.cpp
    ${PARSER_SOURCES}/ParseSprite.cpp
    ${PARSER_SOURCES}/ParseJSONSprite.cpp
    ${PARSER_SOURCES}/RapidJsonErrorHandler.cpp)

add_library(parser STATIC
    ${PARSER}
)

#include_directories(includes)

find_package(rapidjson)

target_link_libraries(parser rapidjson::rapidjson common)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET parser PROPERTY CXX_STANDARD 17)
set_property(TARGET parser PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET parser PROPERTY CXX_EXTENSIONS NO)
