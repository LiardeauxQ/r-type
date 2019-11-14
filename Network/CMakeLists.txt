cmake_minimum_required(VERSION 3.10)

project(network LANGUAGES CXX)


set(NETWORK_SOURCES "${NETWORK_PATH}/sources")

set(NETWORK
    ${NETWORK_SOURCES}/Socket.cpp
    ${NETWORK_SOURCES}/TcpListener.cpp
    ${NETWORK_SOURCES}/TcpStream.cpp
    ${NETWORK_SOURCES}/MessageFactory.cpp
)

add_library(network STATIC
    ${NETWORK}
)

target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET network PROPERTY CXX_STANDARD 17)
set_property(TARGET network PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET network PROPERTY CXX_EXTENSIONS NO)

target_link_libraries(network common)
