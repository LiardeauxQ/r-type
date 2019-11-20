cmake_minimum_required(VERSION 3.10)

set(TESTS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

include_directories (SYSTEM ${CRITERION_INCLUDE_DIRS})

set(TESTS_RTYPE_CLIENT
    ${TESTS_SOURCES}/Client/test_client.cpp
)

set(TESTS_RTYPE_SERVER
    ${TESTS_SOURCES}/Server/test_server.cpp
)

set(TESTS_COMMON
    ${TESTS_SOURCES}/Common/test_common.cpp
)

set(TESTS_ECS
    ${TESTS_SOURCES}/ECS/test_ecs.cpp
    ${TESTS_SOURCES}/ECS/test_thread_pool.cpp
)

set(TESTS_NETWORK
    ${TESTS_SOURCES}/Network/test_network.cpp
)

set(TESTS_PARSER
    ${TESTS_SOURCES}/Parser/test_parser.cpp
    )

set(TESTS_PHYSICS
    ${TESTS_SOURCES}/Physics/AABBCollisionDetection_test.cpp
    ${TESTS_SOURCES}/Physics/SphereCollisionDetection_test.cpp
    ${TESTS_SOURCES}/Physics/OBBCollisionDetection_test.cpp
)

find_package(criterion)

add_executable(test_client
    ${RTYPE_CLIENT}
    ${TESTS_RTYPE_CLIENT}
)

target_include_directories(test_client
    PUBLIC ${RTYPE_CLIENT_PATH}/includes
)

set_property(TARGET test_client PROPERTY CXX_STANDARD 17)
set_property(TARGET test_client PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_client PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(test_client physics ecs common network)
target_link_libraries(test_client ${CRITERION_LIBRARIES})

add_executable(test_server
    ${TESTS_RTYPE_SERVER}
    ${TESTS_SERVER}
)

target_include_directories(test_server
    PUBLIC ${RTYPE_SERVER_PATH}/includes
)

set_property(TARGET test_server PROPERTY CXX_STANDARD 17)
set_property(TARGET test_server PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_server PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(test_server physics ecs common network)
target_link_libraries(test_server ${CRITERION_LIBRARIES})

add_executable(test_common
    ${TESTS_COMMON}
)

set_property(TARGET test_common PROPERTY CXX_STANDARD 17)
set_property(TARGET test_common PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_common PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(test_common common)
target_link_libraries(test_common ${CRITERION_LIBRARIES})

add_executable(test_ecs
    ${TESTS_ECS}
)

set_property(TARGET test_ecs PROPERTY CXX_STANDARD 17)
set_property(TARGET test_ecs PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_ecs PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(test_ecs ecs common)
target_link_libraries(test_ecs ${CRITERION_LIBRARIES})

add_executable(test_network
    ${TESTS_NETWORK}
)

set_property(TARGET test_network PROPERTY CXX_STANDARD 17)
set_property(TARGET test_network PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_network PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(test_network network common)
target_link_libraries(test_network ${CRITERION_LIBRARIES})

add_executable(test_physics
    ${TESTS_PHYSICS}
)

set_property(TARGET test_physics PROPERTY CXX_STANDARD 17)
set_property(TARGET test_physics PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_physics PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(test_physics physics common)
target_link_libraries(test_physics ${CRITERION_LIBRARIES})

add_executable(test_parser
    ${TESTS_PARSER}
    )

file(COPY ${TESTS_SOURCES}/Parser/files DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set_property(TARGET test_parser PROPERTY CXX_STANDARD 17)
set_property(TARGET test_parser PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET test_parser PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(test_parser parser common)
target_link_libraries(test_parser ${CRITERION_LIBRARIES})
