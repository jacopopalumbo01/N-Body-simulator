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

add_compile_options(-I../../../inc -L../../../build -ln-body-sim -I$ENV{mkBoostInc} -L$ENV{mkBoostLib} -lboost_iostreams -lboost_serialization)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
set(OPENMP_FLAGS "-fopenmp")
endif()

find_package(MPI REQUIRED)
# openMPI
add_definitions(-DOMPI_SKIP_MPICXX)

include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(Example_MPI 
                Example_MPI.cpp ${HEADER_FILES})
add_executable(Example_speedup_MPI 
                Example_speedup_MPI.cpp ${HEADER_FILES})

target_compile_options(Example_MPI PRIVATE ${OPENMP_FLAGS})
target_compile_options(Example_speedup_MPI PRIVATE ${OPENMP_FLAGS})

# target_link_libraries(Example NBodyEnvLibrary)
target_link_libraries(Example_MPI OpenMP::OpenMP_CXX ${MPI_C_LIBRARIES} ${CMAKE_SOURCE_DIR}/../../build/libn-body-sim.a $ENV{mkBoostLib}/libboost_iostreams.so $ENV{mkBoostLib}/libboost_serialization.so)
target_link_libraries(Example_speedup_MPI OpenMP::OpenMP_CXX ${MPI_C_LIBRARIES} ${CMAKE_SOURCE_DIR}/../../build/libn-body-sim.a $ENV{mkBoostLib}/libboost_iostreams.so $ENV{mkBoostLib}/libboost_serialization.so)


