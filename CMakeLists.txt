cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(cppslgo VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")

set(CMAKE_BUILD_TYPE Debug)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

enable_testing()
add_subdirectory(./test/)

