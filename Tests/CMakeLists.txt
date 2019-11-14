cmake_minimum_required(VERSION 3.10)
 
include_directories (SYSTEM ${CRITERION_INCLUDE_DIRS})

#set(CLIENT_SOURCES)

set(COMMON_SOURCES "${COMMON_PATH}/sources")
set(SERVER_SOURCES "${SERVER_PATH}/sources")
set(TEST_PATH "${CMAKE_HOME_DIRECTORY}/Tests")

include_directories(
    "${CLIENT_ROOT}/includes"
    "${COMMON_PATH}/includes"
    "${SERVER_ROOT}/includes"
    "${PHYSICS_PATH}/includes"
)

set(TESTS_CLIENT
    ${TEST_PATH}/sources/AABBCollisionDetection_test.cpp
    ${TEST_PATH}/sources/SphereCollisionDetection_test.cpp
    ${TEST_PATH}/sources/OBBCollisionDetection_test.cpp)

set(TESTS_SERVER
    ${TEST_PATH}/sources/test_server.cpp
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
    ${PHYSICS}
)

find_package(criterion)

target_link_libraries(test_client ${CRITERION_LIBRARIES} physics)
target_link_libraries(test_server ${CRITERION_LIBRARIES})

set_property(TARGET test_client PROPERTY CXX_STANDARD 17)
set_property(TARGET test_client PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET test_client PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_server PROPERTY CXX_STANDARD 17)
set_property(TARGET test_server PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_server PROPERTY CXX_STANDARD_REQUIRED YES)
