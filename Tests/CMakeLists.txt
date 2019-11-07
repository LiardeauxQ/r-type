cmake_minimum_required(VERSION 3.10)
 
include_directories (SYSTEM ${CRITERION_INCLUDE_DIRS})

set(CLIENT_SOURCES
    ${CLIENT_PATH}/CollisionDetection.hpp
    ${CLIENT_PATH}/SphereCollisionDetection.cpp
    ${CLIENT_PATH}/SphereCollisionDetection.hpp)

set(COMMON_SOURCES "${COMMON_PATH}/src")
set(SERVER_SOURCES "${SERVER_PATH}/src")
set(TEST_PATH "${CMAKE_HOME_DIRECTORY}/Tests")

include_directories(
    "${CLIENT_ROOT}/inc"
    "${COMMON_ROOT}/inc"
    "${SERVER_ROOT}/inc"
)

add_executable(test_server
    ${RTYPE_SERVER}
    ${RTYPE_COMMON}
    ${TEST_PATH}/test_server.cpp
)

add_executable(test_client
    ${CLIENT_SOURCES}
    ${TEST_PATH}/test_client.cpp
)

find_package(criterion)

target_link_libraries(test_client ${CRITERION_LIBRARIES})

target_link_libraries(test_server ${CRITERION_LIBRARIES})
