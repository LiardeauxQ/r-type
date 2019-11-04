cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)

project(r-type_client)
project(r-type_server)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


# Set compiler arguments
if (NOT WIN32)
	if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE Release)
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -Wno-unused")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -pipe -march=native")
    set(CMAKE_STATIC_LINKER_FLAGS, "-lcriterion")
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

set(SERVER_PATH "${CMAKE_SOURCE_DIR}/Server")
set(CLIENT_PATH "${CMAKE_SOURCE_DIR}/Client")
set(COMMON_PATH "${CMAKE_SOURCE_DIR}/Common")

# Include headers
include_directories(${SERVER_PATH})
include_directories(${COMMON_PATH})
include_directories(${CLIENT_PATH})

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})

set(RTYPE_SERVER
    ${SERVER_PATH}/main.cpp
)

set(RTYPE_CLIENT
	${CLIENT_PATH}/main.cpp
)

set(RTYPE_COMMON
)

add_subdirectory(Tests)

add_executable(r-type_client
    ${RTYPE_CLIENT}
    ${RTYPE_COMMON})

add_executable(r-type_server
    ${RTYPE_SERVER}
    ${RTYPE_COMMON})

find_package(sfml)

# Client link
target_link_libraries(r-type_client sfml::sfml)

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
