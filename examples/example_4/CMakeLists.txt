cmake_minimum_required(VERSION 3.20)
project(N-body)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Set default build type to Release.
if(NOT CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-DBUILD_TYPE_DEBUG)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(HEADER_FILES
    ../../src/Particle/Particle.hpp
    ../../src/System/System.hpp
    ../../src/Functions/Functions.hpp
    ../../src/Exporter/Exporter.hpp
    )

add_library(NBodyEnvLibrary
../../src/Particle/Particle.cpp
../../src/System/System.cpp
../../src/Functions/Functions.cpp
../../src/Exporter/Exporter.cpp
)

add_executable(Example
    ../example_4/example_4.cpp
    ${HEADER_FILES}
)

target_link_libraries(Example NBodyEnvLibrary)


