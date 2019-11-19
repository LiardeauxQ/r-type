cmake_minimum_required(VERSION 3.10)

project(ecs LANGUAGES CXX)

set(ECS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sources")

set(ECS
    ${ECS_SOURCES}/World.cpp
    ${ECS_SOURCES}/StateMachine.cpp
    ${ECS_SOURCES}/AbstractState.cpp
    ${ECS_SOURCES}/Entity.cpp
    ${ECS_SOURCES}/Dispatcher.cpp
    ${ECS_SOURCES}/Transition.cpp
    ${ECS_SOURCES}/EntityRequest.cpp
    ${ECS_SOURCES}/Component.cpp
    ${ECS_SOURCES}/AbstractEvent.cpp
    ${ECS_SOURCES}/EventHandler.cpp)

add_library(ecs STATIC
    ${ECS}
)

target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_property(TARGET ecs PROPERTY CXX_STANDARD 17)
set_property(TARGET ecs PROPERTY CXX_EXTENSIONS NO)
set_property(TARGET ecs PROPERTY CXX_STANDARD_REQUIRED YES)

target_link_libraries(ecs common)