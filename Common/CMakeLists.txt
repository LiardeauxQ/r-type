cmake_minimum_required(VERSION 3.10)

project(r-type_common LANGUAGES CXX)


set(COMMON_SOURCES "${COMMON_PATH}/sources")

set(COMMON
    ${COMMON_SOURCES}/Socket.cpp
    ${COMMON_SOURCES}/TcpListener.cpp
    ${COMMON_SOURCES}/TcpStream.cpp
    ${COMMON_SOURCES}/MessageFactory.cpp
    ${COMMON_SOURCES}/MD5Hasher.cpp
    #${COMMON_SOURCES}/main.cpp
)

add_library(r-type_common STATIC
    ${COMMON}
)

target_include_directories(r-type_common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET r-type_common PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_common PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET r-type_common PROPERTY CXX_EXTENSIONS NO)

target_link_libraries(r-type_common crypto)
