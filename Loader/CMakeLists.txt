cmake_minimum_required(VERSION 3.10)

project(loader LANGUAGES CXX)

set(LOADER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(LOADER
    ${LOADER_SOURCES}/Library.cpp
    ${LOADER_SOURCES}/Loader.cpp
)

add_library(loader STATIC
    ${LOADER}
)

target_include_directories(loader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET loader PROPERTY CXX_STANDARD 17)
set_property(TARGET loader PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET loader PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(loader common ecs)