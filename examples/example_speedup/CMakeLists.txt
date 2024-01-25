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

add_compile_options(-I../../../inc -L../../../build -I$ENV{mkBoostInc} -L$ENV{mkBoostLib} -lboost_iostreams -lboost_serialization -Ofast -funroll-all-loops)

find_package(MPI REQUIRED)
# openMPI
add_definitions(-DOMPI_SKIP_MPICXX)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
set(OPENMP_FLAGS "-fopenmp")
endif()

add_executable(Example
example_speedup.cpp
${HEADER_FILES}
)

add_executable(BHspeedup
example_BHspeedup.cpp
${HEADER_FILES}
)

target_compile_options(Example PRIVATE ${OPENMP_FLAGS})
target_compile_options(BHspeedup PRIVATE ${OPENMP_FLAGS})

target_include_directories(Example PRIVATE 
    ../../inc/
)

target_include_directories(BHspeedup PRIVATE 
    ../../inc/
)

# target_link_libraries(Example NBodyEnvLibrary)
target_link_libraries(Example OpenMP::OpenMP_CXX ${MPI_C_LIBRARIES} ${CMAKE_SOURCE_DIR}/../../build/libn-body-sim.a $ENV{mkBoostLib}/libboost_iostreams.so $ENV{mkBoostLib}/libboost_serialization.so)
target_link_libraries(BHspeedup OpenMP::OpenMP_CXX ${MPI_C_LIBRARIES} ${CMAKE_SOURCE_DIR}/../../build/libn-body-sim.a $ENV{mkBoostLib}/libboost_iostreams.so $ENV{mkBoostLib}/libboost_serialization.so)



