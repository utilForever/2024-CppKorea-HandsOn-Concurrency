# CMake version
cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

# Declare project
project(cpp-concurrency)

# Use standard as C++23
set(CMAKE_CXX_STANDARD 23)

# Add example directories
add_subdirectory("2_Example/01_Create_Thread")
add_subdirectory("2_Example/02_Thread_Functions")
add_subdirectory("2_Example/03_Wait_Kill_Detach")
add_subdirectory("2_Example/04_Race_Condition")
add_subdirectory("2_Example/05_Mutex_and_Locks")
add_subdirectory("2_Example/06_Lock_Guard")
add_subdirectory("2_Example/07_Scoped_Lock")
add_subdirectory("2_Example/08_Unique_Lock")
add_subdirectory("2_Example/09_Shared_Lock")
add_subdirectory("2_Example/10_Timed_Mutex")
add_subdirectory("2_Example/11_Recursive_Mutex")
add_subdirectory("2_Example/12_Recursive_Timed_Mutex")
