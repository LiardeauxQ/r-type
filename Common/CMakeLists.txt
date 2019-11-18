cmake_minimum_required(VERSION 3.10)

project(common LANGUAGES CXX)

set(COMMON_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(COMMON
    ${COMMON_SOURCES}/MD5Hasher.cpp
    ${COMMON_SOURCES}/Frame.cpp
)

add_library(common STATIC
    ${COMMON}
)

target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET common PROPERTY CXX_STANDARD 17)
set_property(TARGET common PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET common PROPERTY CXX_STANDARD_REQUIRED YES)

if (NOT APPLE)
    target_link_libraries(common crypto)
endif()
