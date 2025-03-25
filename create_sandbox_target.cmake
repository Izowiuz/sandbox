function(create_sandbox_target tag target_name)

set(options "")
set(one_value_args "ADDITIONAL_COMPILE_FLAGS")
set(multi_value_args "")
cmake_parse_arguments(PARSE_ARGV 0 arg "${options}" "${one_value_args}" "${multi_value_args}")

set(SANDBOX_TARGET_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${tag}/${target_name}/")
message("Target path: ${SANDBOX_TARGET_PATH}")

set(full_target_name ${tag}-${target_name})

if (NOT EXISTS "${SANDBOX_TARGET_PATH}")
    message(FATAL_ERROR "Directory: ${SANDBOX_TARGET_PATH} do not exists.")
endif()

file(
GLOB_RECURSE
    source_files
    "${SANDBOX_TARGET_PATH}/src/*.*"
)

file(
GLOB_RECURSE
    tests_sources
    "${SANDBOX_TARGET_PATH}/*Tests.cpp"
)

LIST(LENGTH tests_sources tests_sources_count)
if (tests_sources_count)
    message("Found tests for: ${full_target_name}")

    add_executable(
        ${full_target_name}-tests
        ""
    )

    target_sources(
        ${full_target_name}-tests
    PRIVATE
        ${source_files}
        ${tests_sources}
    )

    target_include_directories(
        ${full_target_name}-tests
    PRIVATE
        $<BUILD_INTERFACE:${SANDBOX_TARGET_PATH}/src>
    )

    target_link_libraries(
        ${full_target_name}-tests
    PRIVATE
        spdlog::spdlog
        GTest::gtest
        GTest::gtest_main
    )

    set_property(
    TARGET
        ${full_target_name}-tests
    PROPERTY
        CXX_STANDARD 20
    )
else()
    message("No tests found for: ${full_target_name}")
endif()

if (EXISTS "${SANDBOX_TARGET_PATH}/main.cpp")
    message("Found main for: ${full_target_name}")

    add_executable(
        ${full_target_name}
        ""
    )

    target_sources(
        ${full_target_name}
    PRIVATE
        ${source_files}
        ${SANDBOX_TARGET_PATH}/main.cpp
    )

    target_include_directories(
        ${full_target_name}
    PRIVATE
        $<BUILD_INTERFACE:${SANDBOX_TARGET_PATH}/src>
    )

    target_link_libraries(
        ${full_target_name}
    PRIVATE
        spdlog::spdlog
    )

    set_property(
    TARGET
        ${full_target_name}
    PROPERTY
        CXX_STANDARD 20
    )

    if (arg_ADDITIONAL_COMPILE_FLAGS)
        message("For target: ${target_name} - ADDITIONAL_COMPILE_FLAGS set to: ${arg_ADDITIONAL_COMPILE_FLAGS}")
        target_compile_options(${full_target_name} PRIVATE ${arg_ADDITIONAL_COMPILE_FLAGS})
    endif()

else()
    message("No main found for: ${full_target_name}")
endif()

endfunction()
