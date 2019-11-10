cmake_minimum_required(VERSION 3.10)
 
include_directories (SYSTEM ${CRITERION_INCLUDE_DIRS})

set(COMMON_SOURCES "${COMMON_PATH}/src")
set(SERVER_SOURCES "${SERVER_PATH}/src")
set(TEST_PATH "${CMAKE_HOME_DIRECTORY}/Tests")

include_directories(
    "${CLIENT_ROOT}/inc"
    "${COMMON_ROOT}/inc"
    "${SERVER_ROOT}/inc"
)

set(TESTS_CLIENT
    ${TEST_PATH}/src/test_client.cpp
)

set(TESTS_SERVER
    ${TEST_PATH}/src/test_server.cpp
)

add_executable(test_server
    ${RTYPE_SERVER}
    ${RTYPE_COMMON}
    ${TESTS_SERVER}
)

add_executable(test_client
    ${RTYPE_CLIENT}
    ${RTYPE_COMMON}
    ${TESTS_CLIENT}
)

find_package(criterion)

target_link_libraries(test_client ${CRITERION_LIBRARIES})
target_link_libraries(test_server ${CRITERION_LIBRARIES})

set_property(TARGET test_client PROPERTY CXX_STANDARD 17)
set_property(TARGET test_client PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET test_client PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_server PROPERTY CXX_STANDARD 17)
set_property(TARGET test_server PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_server PROPERTY CXX_STANDARD_REQUIRED YES)
