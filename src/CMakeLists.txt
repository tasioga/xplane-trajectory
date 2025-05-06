cmake_minimum_required(VERSION 3.6)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Add debug flags
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
endif()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    "/usr/local/include"
)

# This is the default installation for GeographicLib and xplaneconnect
link_directories("/usr/local/lib")

set(SRC main.cpp trajectory.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${CMAKE_PROJECT_NAME} -lGeographicLib -lxplaneconnect)