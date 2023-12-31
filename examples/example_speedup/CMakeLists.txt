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

# set(HEADER_FILES
#     ../../inc/Particle/Particle.hpp
#     ../../inc/System/System.hpp
#     ../../inc/Functions/Functions.hpp
#     ../../inc/Exporter/Exporter.hpp
#     ../../inc/Collisions/Collisions.hpp
#     ../../inc/Functions/EulerDiscretizer.hpp
#     ../../inc/Functions/VerletDiscretizer.hpp
#     )

set(HEADER_DIR ../../inc)
set(HEADER_FILES
    Particle/Particle.hpp
    System/System.hpp
    Functions/Functions.hpp
    Exporter/Exporter.hpp
    Collisions/Collisions.hpp
    Functions/EulerDiscretizer.hpp
    Functions/VerletDiscretizer.hpp
)

# Create a full path for each header file
foreach(HEADER ${HEADER_FILES})
    list(APPEND FULL_HEADER_PATH "${HEADER_DIR}/${HEADER}")
endforeach()

# Define variables for source files
set(SOURCE_DIR ../../src)
set(SOURCE_FILES
    Particle/Particle.cpp
    System/System.cpp
    Functions/Functions.cpp
    Exporter/Exporter.cpp
    Collisions/Collisions.cpp
    Functions/EulerDiscretizer.cpp
    Functions/VerletDiscretizer.cpp
)

# Create a full path for each source file
foreach(SOURCE ${SOURCE_FILES})
    list(APPEND FULL_SOURCE_PATH "${SOURCE_DIR}/${SOURCE}")
endforeach()

# Add library using the variables
add_library(NBodyEnvLibrary ${FULL_HEADER_PATH} ${FULL_SOURCE_PATH})

# add_library(NBodyEnvLibrary
#     ../../src/Particle/Particle.cpp
#     ../../src/System/System.cpp
#     ../../src/Functions/Functions.cpp
#     ../../src/Exporter/Exporter.cpp
#     ../../src/Collisions/Collisions.cpp
#     ../../src/Functions/EulerDiscretizer.cpp
#     ../../src/Functions/VerletDiscretizer.cpp
# )

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
set(OPENMP_FLAGS "-fopenmp")
endif()

# Add executable using the library and headers
add_executable(Example
    ../example_speedup/example_speedup.cpp
    ${FULL_HEADER_PATH}  # Use the variables here
    ${FULL_SOURCE_PATH}  # Use the variables here
)

target_compile_options(Example PRIVATE ${OPENMP_FLAGS})

target_include_directories(Example PRIVATE 
    ../../inc/
)

target_include_directories(NBodyEnvLibrary PUBLIC 
    ../../inc/
)

# target_link_libraries(Example NBodyEnvLibrary)
target_link_libraries(Example NBodyEnvLibrary OpenMP::OpenMP_CXX)
target_link_libraries(NBodyEnvLibrary PUBLIC OpenMP::OpenMP_CXX)


