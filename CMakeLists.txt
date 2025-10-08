cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23 CACHE STRING "C++ standard")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sandbox)
include(CTest)

include(cmake/create_sandbox_target.cmake)
include(cmake/dependencies.cmake)

include(categories/types.cmake)
include(categories/algorithms.cmake)
include(categories/adl.cmake)
include(categories/beautiful-c++.cmake)
include(categories/c++-software-design.cmake)
include(categories/random.cmake)
include(categories/programming-with-c++20.cmake)
include(categories/a-tour-of-cpp.cmake)
include(categories/linkedin-learning-functional-programming-in-c++.cmake)
