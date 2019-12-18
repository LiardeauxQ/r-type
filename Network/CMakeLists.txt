cmake_minimum_required(VERSION 3.10)

project(network LANGUAGES CXX)

set(NETWORK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(NETWORK
    ${NETWORK_SOURCES}/Socket.cpp
    ${NETWORK_SOURCES}/TcpListener.cpp
    ${NETWORK_SOURCES}/TcpStream.cpp
    ${NETWORK_SOURCES}/MessageFactory.cpp
    ${NETWORK_SOURCES}/Message.cpp
    ${NETWORK_SOURCES}/Protocol/JoinGame.cpp
    ${NETWORK_SOURCES}/Protocol/CreateGame.cpp
    ${NETWORK_SOURCES}/Protocol/PacketDispatcher.cpp
)

add_library(network STATIC
    ${NETWORK}
)

target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET network PROPERTY CXX_STANDARD 17)
set_property(TARGET network PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET network PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(network common)
