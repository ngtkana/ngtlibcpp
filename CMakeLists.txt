cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(cppslgo VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")

enable_testing()
add_subdirectory(./test/)

