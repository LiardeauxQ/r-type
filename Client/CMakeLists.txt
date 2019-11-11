cmake_minimum_required(VERSION 3.10)

project(r-type_client LANGUAGES CXX)

set(TEST_PATH "${CMAKE_HOME_DIRECTORY}/Tests")

set(CLIENT_SOURCES "${CLIENT_PATH}/src")

set(RTYPE_CLIENT
	${CLIENT_PATH}/src/main.cpp
)

add_executable(r-type_client
    ${RTYPE_CLIENT}
)

target_link_libraries(r-type_client ecs)

set_property(TARGET r-type_client PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_client PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET r-type_client PROPERTY CXX_EXTENSIONS NO)

find_package(sfml)

target_link_libraries(r-type_client sfml::sfml)
