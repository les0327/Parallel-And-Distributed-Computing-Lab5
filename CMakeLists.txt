cmake_minimum_required(VERSION 3.8)
project(ParallelAndDistributedComputingLab5)

# added -fopenmp
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c functions.h functions.c)
add_executable(ParallelAndDistributedComputingLab5 ${SOURCE_FILES})