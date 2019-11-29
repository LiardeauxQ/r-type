cmake_minimum_required(VERSION 3.10)

project(r-type_server LANGUAGES CXX)

set(RTYPE_SERVER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(RTYPE_SERVER
    ${RTYPE_SERVER_SOURCES}/main.cpp
)

add_executable(r-type_server
    ${RTYPE_SERVER}
)

target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET r-type_server PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_server PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET r-type_server PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(r-type_server ecs common network loader)

if (NOT APPLE)
    target_link_libraries(r-type_server crypto)
endif()
