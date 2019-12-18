cmake_minimum_required(VERSION 3.10)

project(r-type_client LANGUAGES CXX)


set(RTYPE_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(RTYPE_CLIENT
	${RTYPE_CLIENT_SOURCES}/main.cpp
	${RTYPE_CLIENT_SOURCES}/Game.cpp
	${RTYPE_CLIENT_SOURCES}/InputOptionsHandler.cpp
	${RTYPE_CLIENT_SOURCES}/ClientPacketDispatcher.cpp
	)

add_executable(r-type_client
    ${RTYPE_CLIENT}
)

find_package(sfml)

target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET r-type_client PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_client PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET r-type_client PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(r-type_client ecs common physics network parser loader sfml::sfml)
