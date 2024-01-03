cmake_minimum_required(VERSION 3.10)

project(kmeans)

# Set build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Include the directory where k-means.h and k-means.cpp are located
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(kmeans main.cpp src/k-means.cpp)

set(EXECUTABLE_OUTPUT_PATH ../exec)
