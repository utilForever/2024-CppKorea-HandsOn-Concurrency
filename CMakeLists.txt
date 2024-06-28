# CMake version
cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

# Declare project
project(cpp-concurrency)

# Use standard as C++23
set(CMAKE_CXX_STANDARD 23)

# Add example directories
add_subdirectory("2_Example/01_Create_Thread")
