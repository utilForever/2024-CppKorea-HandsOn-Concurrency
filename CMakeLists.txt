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
add_subdirectory("2_Example/13_Shared_Timed_Mutex")
add_subdirectory("2_Example/14_Condition_Variables_Basic")
add_subdirectory("2_Example/15_Condition_Variables_Notify_All")
add_subdirectory("2_Example/16_Condition_Variables_Timed_Wait")
add_subdirectory("2_Example/17_Condition_Variables_Spurious_Wakeup")
add_subdirectory("2_Example/18_Atomics_Basic")
add_subdirectory("2_Example/19_Atomics_Boolean")
add_subdirectory("2_Example/20_Atomics_Pointer")
add_subdirectory("2_Example/21_Atomics_Flag")
add_subdirectory("2_Example/22_Atomics_Operation")
add_subdirectory("2_Example/23_Atomics_Is_Lockfree")
