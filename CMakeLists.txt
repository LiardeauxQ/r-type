cmake_minimum_required(VERSION 3.10.0)

project(R-Type)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Documents/.cmake")

# Set compiler arguments
if (NOT WIN32)
	if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE Debug)
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wdouble-promotion -Wformat=2 -Wno-unused")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -pipe -march=native -Wno-old-style-cast")
	set(CMAKE_EXE_LINKER_FLAGS "-export-dynamic")
	set(CMAKE_STATIC_LINKER_FLAGS, "-lcriterion")
else()
	set(NO_TEST)
endif ()

if (APPLE)
	add_definitions(-DAPPLE)
elseif (WIN32)
	add_definitions(-DWINDOWS)
	add_definitions(-D_WIN32_WINNT=0x0A00)
endif (APPLE)

# Include conan headers
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup()
else()
	message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

if (UNIX)
	include_directories("${CMAKE_HOME_DIRECTORY}/.conan/data")
endif ()

if (NO_TEST)
elseif()
	find_package(Criterion)
	set(CRITERION_LIBRARIES criterion)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

set(RTYPE_CLIENT_PATH "${CMAKE_SOURCE_DIR}/Client")
set(RTYPE_SERVER_PATH "${CMAKE_SOURCE_DIR}/Server")
if (NO_TEST)
	set(TESTS_PATH,  "${CMAKE_SOURCE_DIR}/Tests")
endif()
set(COMMON_PATH  "${CMAKE_SOURCE_DIR}/Common")
set(ECS_PATH 	 "${CMAKE_SOURCE_DIR}/ECS")
set(PHYSICS_PATH "${CMAKE_SOURCE_DIR}/Physics")
set(NETWORK_PATH "${CMAKE_SOURCE_DIR}/Network")

add_subdirectory(Client)
add_subdirectory(Server)
if (NO_TEST)
	add_subdirectory(Tests)
endif()
add_subdirectory(Common)
add_subdirectory(ECS)
add_subdirectory(Physics)
add_subdirectory(Parser)
add_subdirectory(Network)
add_subdirectory(Loader)

# Client link

#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions

# Server link
# target_link_libraries(r-type_client)

# Copy dll to the binary folder
# if(WIN32)
#     if ($<CONFIG:Debug>)
#         get_target_property(WIDGETDLL Qt5::Widgets IMPORTED_LOCATION_DEBUG)
#     else ($<CONFIG:Debug>)
#         get_target_property(WIDGETDLL Qt5::Widgets IMPORTED_LOCATION_RELEASE)
# 	endif ($<CONFIG:Debug>)
# 
# 	add_custom_command (
#     	TARGET babel-client POST_BUILD
#     	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:babel-client>
#     	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:babel-client>
#     	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:babel-client>
# 	)
# endif(WIN32)
