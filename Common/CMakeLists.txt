cmake_minimum_required(VERSION 3.10)

set(CLIENT_SOURCES "${CLIENT_PATH}/sources")
set(COMMON_SOURCES "${COMMON_PATH}/sources")
set(SERVER_SOURCES "${SERVER_PATH}/sources")

set(TEST_PATH "${CMAKE_HOME_DIRECTORY}/Tests")

set(RTYPE_COMMON
    ${COMMON_SOURCES}/Socket.cpp
    ${COMMON_SOURCES}/TcpStream.cpp
    ${COMMON_SOURCES}/TcpListener.cpp
    ${COMMON_SOURCES}/Protocol/CreateRoom.cpp
PARENT_SCOPE)

include_directories(
    "${COMMON_PATH}/includes"
)
