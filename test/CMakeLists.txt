message(STATUS "Building unit tests...")
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

include_directories(
   ${CMAKE_CURRENT_LIST_DIR}/../Catch2/single_include
   ${CMAKE_CURRENT_LIST_DIR}/../include
  )

add_library(test_main ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

enable_testing()

# Listing test targets
file(GLOB targets RELATIVE ${CMAKE_CURRENT_LIST_DIR} *-test/*.cpp)
foreach(target ${targets})
  get_filename_component(test_name ${target} DIRECTORY)
  message(${test_name})
  if(NOT TARGET ${test_name})
    file(GLOB source RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${test_name}/*.cpp)
    add_executable(${test_name} ${source})
    target_link_libraries(${test_name} test_main ${OpenCASCADE_LIBRARIES})
    add_test(NAME ${test_name} COMMAND ${test_name})
  endif()
endforeach()

