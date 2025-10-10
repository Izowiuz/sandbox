include(FetchContent)

find_package(GTest CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Boost REQUIRED COMPONENTS hana)

FetchContent_Declare(
    RxCpp
    GIT_REPOSITORY "https://github.com/ReactiveX/RxCpp.git"
    GIT_TAG "v4.1.1"
    PATCH_COMMAND git apply ${CMAKE_SOURCE_DIR}/patches/rx-notification.hpp.const_rxu_error_ptr.diff
    UPDATE_DISCONNECTED 1
)
FetchContent_MakeAvailable(RxCpp)
