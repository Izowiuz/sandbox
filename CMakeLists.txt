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

create_sandbox_target("c++-software-design" "classic-visitor")
create_sandbox_target("c++-software-design" "std-visit-visitor")
create_sandbox_target("c++-software-design" "acyclic-visitor")
create_sandbox_target("c++-software-design" "strategy")
create_sandbox_target("c++-software-design" "strategy-std-function")
create_sandbox_target("c++-software-design" "command")
create_sandbox_target("c++-software-design" "object-adapter")
create_sandbox_target("c++-software-design" "class-adapter")
create_sandbox_target("c++-software-design" "tagged-pull-observer")
create_sandbox_target("c++-software-design" "tagged-pull-observer-std-function")
create_sandbox_target("c++-software-design" "crtp")
create_sandbox_target("c++-software-design" "crtp-mixin-strong-type")
create_sandbox_target("algorithms" "merge-sort")
create_sandbox_target("adl" "swap")
create_sandbox_target("adl" "begin-end")
create_sandbox_target("types" "class-id")
create_sandbox_target("random" "virtual-destructor")
create_sandbox_target("random" "const-span")
create_sandbox_target("random" "fold-expressions")
create_sandbox_target("talks" "inheritance-is-the-base-class-of-evil")

