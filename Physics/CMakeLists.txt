cmake_minimum_required(VERSION 3.10)

project(physics LANGUAGES CXX)

set(PHYSICS_SOURCES "${PHYSICS_PATH}/sources")

set(PHYSICS
    ${PHYSICS_SOURCES}/AABBCollisionDetection.cpp
    ${PHYSICS_SOURCES}/OBBCollisionDetection.cpp
    ${PHYSICS_SOURCES}/SphereCollisionDetection.cpp
    ${PHYSICS_SOURCES}/GeometryObject.cpp
)

add_library(physics STATIC
    ${PHYSICS}
)

include_directories(includes)

target_include_directories(physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET physics PROPERTY CXX_STANDARD 17)
set_property(TARGET physics PROPERTY CXX_STANDARD_REQUIRED YES)
set_property(TARGET physics PROPERTY CXX_EXTENSIONS NO)
