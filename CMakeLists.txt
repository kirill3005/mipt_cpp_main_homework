cmake_minimum_required(VERSION 3.10)
project(mipt_cpp_main_homework CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(task1 task1/main.cpp)
add_executable(task2 task2/main.cpp)
add_executable(task3 task3/main.cpp)
add_executable(task4 task4/main.cpp)
