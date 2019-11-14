cmake_minimum_required(VERSION 3.10)

project(r-type_client LANGUAGES CXX)

set(CLIENT_SOURCES "${CLIENT_PATH}/sources")
set(COMMON_SOURCES "${COMMON_PATH}/sources")
set(SERVER_SOURCES "${SERVER_PATH}/sources")

set(TEST_PATH "${CMAKE_HOME_DIRECTORY}/Tests")

set(CLIENT_SOURCES "${CLIENT_PATH}/sources")

set(RTYPE_CLIENT
	${CLIENT_PATH}/sources/main.cpp
)

include_directories(
    "${CLIENT_ROOT}/includes"
)

add_executable(r-type_client
    ${RTYPE_CLIENT}
)

target_link_libraries(r-type_client ecs r-type_common physics)

set_property(TARGET r-type_client PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_client PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET r-type_client PROPERTY CXX_EXTENSIONS NO)

find_package(sfml)

target_link_libraries(r-type_client sfml::sfml)
