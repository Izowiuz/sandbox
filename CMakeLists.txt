cmake_minimum_required(VERSION 3.28)

include(cmake/create_sandbox_target.cmake)

project(sandbox)
include(CTest)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS hana)

include(categories/types.cmake)
include(categories/algorithms.cmake)
include(categories/adl.cmake)
include(categories/beautiful-c++.cmake)
include(categories/c++-software-design.cmake)
include(categories/random.cmake)
include(categories/programming-with-c++20.cmake)
include(categories/a-tour-of-cpp.cmake)
include(categories/linkedin-learning-functional-programming-in-c++.cmake)
