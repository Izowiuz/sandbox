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

create_sandbox_target("types" "class-id")

create_sandbox_target("adl" "swap")
create_sandbox_target("adl" "begin-end")

create_sandbox_target("talks" "inheritance-is-the-base-class-of-evil")

create_sandbox_target("patterns" "classic-visitor")
create_sandbox_target("patterns" "std-visit-visitor")
create_sandbox_target("patterns" "acyclic-visitor")
create_sandbox_target("patterns" "strategy")
