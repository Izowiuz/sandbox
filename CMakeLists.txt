cmake_minimum_required(VERSION 3.20)

include(create_sandbox_target.cmake)

project(sandbox)
include(CTest)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

create_sandbox_target("types" "class-id")

create_sandbox_target("algorithms" "merge-sort")

create_sandbox_target("adl" "swap")
create_sandbox_target("adl" "begin-end")

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

create_sandbox_target("beautiful-c++" "function-overloading-conversion-problem")
create_sandbox_target("beautiful-c++" "member-initialization-order")
create_sandbox_target("beautiful-c++" "structured-bindings")

create_sandbox_target("random" "virtual-destructor")
create_sandbox_target("random" "const-span")
create_sandbox_target("random" "fold-expressions")
create_sandbox_target("random" "structured-bindings")
create_sandbox_target("random" "modules-test"
ADDITIONAL_COMPILE_FLAGS
    "-fmodules-ts"
)

create_sandbox_target("programming-with-c++20" "add")
create_sandbox_target("programming-with-c++20" "abbreviated-function-template")
create_sandbox_target("programming-with-c++20" "conditional-call")
create_sandbox_target("programming-with-c++20" "coroutines-int-generator")
create_sandbox_target("programming-with-c++20" "coroutines-parse-v1")
create_sandbox_target("programming-with-c++20" "ranges-introduction")
create_sandbox_target("programming-with-c++20" "ranges-custom-view")
create_sandbox_target("programming-with-c++20" "std-format")
create_sandbox_target("programming-with-c++20" "spaceship-operator")
create_sandbox_target("programming-with-c++20" "default-constructible-lambdas")
create_sandbox_target("programming-with-c++20" "captureless-lambdas-in-unevaluated-contexts")
create_sandbox_target("programming-with-c++20" "templated-lambdas")
create_sandbox_target("programming-with-c++20" "designated-initializers")
create_sandbox_target("programming-with-c++20" "bitcast")
create_sandbox_target("programming-with-c++20" "toarray")
create_sandbox_target("programming-with-c++20" "for-loop-with-initializer")
