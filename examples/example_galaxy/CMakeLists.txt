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

add_compile_options(-I../../../include -L../../../build -I$ENV{mkBoostInc} -L$ENV{mkBoostLib} -lboost_iostreams -lboost_serialization -Ofast -funroll-all-loops)

include_directories(../../include)

add_library(NBodyEnvLibrary
../../src/Particle/Particle.cpp
../../src/System/System.cpp
../../src/Functions/Functions.cpp
../../src/Functions/EulerDiscretizer.cpp
../../src/Functions/VerletDiscretizer.cpp
../../src/Functions/RKDiscretizer.cpp
../../src/Exporter/Exporter.cpp
../../src/Collisions/Collisions.cpp
../../src/Simulator/Simulator.cpp
../../src/TreeNode/TreeNode.cpp
)

find_package(MPI REQUIRED)
# openMPI
add_definitions(-DOMPI_SKIP_MPICXX)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
set(OPENMP_FLAGS "-fopenmp")
endif()

add_executable(Galaxy
    example_galaxy.cpp
    ${HEADER_FILES}
)

add_executable(StarCluster
    example_star_cluster.cpp
    ${HEADER_FILES}
)

add_executable(RotatingDisk
    example_rotating_disk.cpp
    ${HEADER_FILES}
)

target_link_libraries(Galaxy NBodyEnvLibrary OpenMP::OpenMP_CXX ${MPI_C_LIBRARIES} ${CMAKE_SOURCE_DIR}/../../build/libn-body-sim.a $ENV{mkBoostLib}/libboost_iostreams.so $ENV{mkBoostLib}/libboost_serialization.so)
target_link_libraries(StarCluster NBodyEnvLibrary OpenMP::OpenMP_CXX ${MPI_C_LIBRARIES} ${CMAKE_SOURCE_DIR}/../../build/libn-body-sim.a $ENV{mkBoostLib}/libboost_iostreams.so $ENV{mkBoostLib}/libboost_serialization.so)
target_link_libraries(RotatingDisk NBodyEnvLibrary OpenMP::OpenMP_CXX ${MPI_C_LIBRARIES} ${CMAKE_SOURCE_DIR}/../../build/libn-body-sim.a $ENV{mkBoostLib}/libboost_iostreams.so $ENV{mkBoostLib}/libboost_serialization.so)