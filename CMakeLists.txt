cmake_minimum_required(VERSION 3.10)

# Set the project name
project(AlgorithmStudy)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER /usr/bin/g++-13 CACHE STRING "C++ compiler" FORCE) 

# Include directories
add_subdirectory(src)

