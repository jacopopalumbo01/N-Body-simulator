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
    ../../src/ParallelSystem/ParallelSystem.hpp
    ../../src/Functions/Functions.hpp
    )

add_library(NBodyEnvLibrary
../../src/Particle/Particle.cpp
../../src/System/System.cpp
../../src/ParallelSystem/ParallelSystem.cpp
../../src/Functions/Functions.cpp
../../src/Exporter/Exporter.cpp
)

add_executable(Example
    ../example_parallel/example_parallel.cpp
    ${HEADER_FILES}
    )

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(Example PUBLIC OpenMP::OpenMP_CXX NBodyEnvLibrary)
    target_link_libraries(NBodyEnvLibrary PUBLIC OpenMP::OpenMP_CXX)
endif()

# # add import library for OpenMP
# find_package(OpenMP REQUIRED)

#     # add OpenMP flags
# target_compile_options(Example PRIVATE ${OpenMP_CXX_FLAGS})





