cmake_minimum_required(VERSION 3.10)

project(r-type_client LANGUAGES CXX)


set(RTYPE_CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(RTYPE_CLIENT
	${RTYPE_CLIENT_SOURCES}/main.cpp
	${RTYPE_CLIENT_SOURCES}/DrawSystem.cpp
	${RTYPE_CLIENT_SOURCES}/MainMenuState.cpp
	${RTYPE_CLIENT_SOURCES}/MovementSystem.cpp
	${RTYPE_CLIENT_SOURCES}/WithParameterSystem.cpp
	${RTYPE_CLIENT_SOURCES}/SystemNetworkEvent.cpp
    ${RTYPE_CLIENT_SOURCES}/SFMLEventProducer.cpp
	${RTYPE_CLIENT_SOURCES}/GraphicBundle.cpp

)

add_executable(r-type_client
    ${RTYPE_CLIENT}
)

find_package(sfml)

target_include_directories(r-type_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET r-type_client PROPERTY CXX_STANDARD 17)
set_property(TARGET r-type_client PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET r-type_client PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(r-type_client ecs common physics network parser sfml::sfml)
