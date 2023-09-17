cmake_minimum_required(VERSION 3.20)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

include(create_sandbox_target.cmake)

project(sandbox)
include(CTest)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

create_sandbox_target("algorithms" "merge-sort")

create_sandbox_target("adl" "swap")
