cmake_minimum_required(VERSION 3.10)

project(r-type_server LANGUAGES CXX)

set(CLIENT_SOURCES "${CLIENT_PATH}/sources")
set(COMMON_SOURCES "${COMMON_PATH}/sources")
set(SERVER_SOURCES "${SERVER_PATH}/sources")

set(TEST_PATH "${CMAKE_HOME_DIRECTORY}/Tests")

set(RTYPE_SERVER
    ${SERVER_PATH}/sources/main.cpp
    #${SERVER_PATH}/sources/GameServer.cpp
    #${SERVER_PATH}/sources/GameRoom.cpp
    #${SERVER_PATH}/sources/Client.cpp
)

add_executable(r-type_server
    ${RTYPE_SERVER}
)

target_include_directories(r-type_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET r-type_server PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_server PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET r-type_server PROPERTY CXX_EXTENSIONS NO)

target_link_libraries(r-type_server ecs common network)
target_link_libraries(r-type_server crypto)
