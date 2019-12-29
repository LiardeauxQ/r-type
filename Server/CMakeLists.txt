cmake_minimum_required(VERSION 3.10)

project(r-type_server LANGUAGES CXX)

set(RTYPE_SERVER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(RTYPE_SERVER
    ${RTYPE_SERVER_SOURCES}/main.cpp
    ${RTYPE_SERVER_SOURCES}/Application.cpp
    ${RTYPE_SERVER_SOURCES}/Lobby.cpp
    ${RTYPE_SERVER_SOURCES}/GameRoom.cpp
    ${RTYPE_SERVER_SOURCES}/Client.cpp
    ${RTYPE_SERVER_SOURCES}/Entity.cpp
    ${RTYPE_SERVER_SOURCES}/Spawner.cpp
    ${RTYPE_SERVER_SOURCES}/Bullet.cpp
)

add_executable(r-type_server
    ${RTYPE_SERVER}
)

target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET r-type_server PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_server PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET r-type_server PROPERTY CXX_STANDARD_REQUIRED YES)

find_package(boost_asio)

target_link_libraries(r-type_server common network loader ecs boost_asio::boost_asio)

if (NOT APPLE)
    target_link_libraries(r-type_server crypto)
endif()
