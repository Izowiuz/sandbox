function(create_sandbox_target tag target_name)

set(options "")
set(one_value_args "ADDITIONAL_COMPILE_FLAGS")
set(multi_value_args "ADDITIONAL_LIBRARIES")
cmake_parse_arguments(PARSE_ARGV 0 arg "${options}" "${one_value_args}" "${multi_value_args}")

set(sandbox_target_path "${CMAKE_CURRENT_SOURCE_DIR}/categories/${tag}/${target_name}/")
message(STATUS "Target path: ${sandbox_target_path}")

# create target path
file(
    MAKE_DIRECTORY "${sandbox_target_path}"
)

set(main_cpp "${sandbox_target_path}/main.cpp")
set(full_target_name ${tag}-${target_name})

# copy main.cpp template
if(NOT EXISTS "${main_cpp}")
    file(
        COPY_FILE
            "${CMAKE_CURRENT_SOURCE_DIR}/templates/main.cpp-template"
            "${sandbox_target_path}/main.cpp"
    )
endif()

file(
GLOB_RECURSE
    source_files
    "${sandbox_target_path}/src/*.*"
)

file(
GLOB_RECURSE
    tests_sources
    "${sandbox_target_path}/*Tests.cpp"
)

LIST(LENGTH tests_sources tests_sources_count)
if (tests_sources_count)
    message(STATUS "Found tests for: ${full_target_name}")

    add_executable(
        ${full_target_name}-tests
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
        $<BUILD_INTERFACE:${sandbox_target_path}/src>
    )

    target_link_libraries(
        ${full_target_name}-tests
    PRIVATE
        spdlog::spdlog
        GTest::gtest
        GTest::gtest_main
    )

    set_target_properties(
        ${full_target_name}-tests
    PROPERTIES
        FOLDER "${tag}"
    )

else()
    message(STATUS "No tests found for: ${full_target_name}")
endif()

if (EXISTS "${sandbox_target_path}/main.cpp")
    message(STATUS "Found main for: ${full_target_name}")

    add_executable(
        ${full_target_name}
    )

    target_sources(
        ${full_target_name}
    PRIVATE
        ${source_files}
        ${sandbox_target_path}/main.cpp
    )

    target_include_directories(
        ${full_target_name}
    PRIVATE
        $<BUILD_INTERFACE:${sandbox_target_path}/src>
    )

    target_link_libraries(
        ${full_target_name}
    PRIVATE
        spdlog::spdlog
    )

    set_target_properties(
        ${full_target_name}
    PROPERTIES
        FOLDER "${tag}"
    )

    if (arg_ADDITIONAL_COMPILE_FLAGS)
        message(STATUS "For target: ${target_name} - ADDITIONAL_COMPILE_FLAGS set to: ${arg_ADDITIONAL_COMPILE_FLAGS}")
        target_compile_options(${full_target_name} PRIVATE ${arg_ADDITIONAL_COMPILE_FLAGS})
    endif()

    if (arg_ADDITIONAL_LIBRARIES)
        message(STATUS "For target: ${target_name} - arg_ADDITIONAL_LIBRARIES set to: ${arg_ADDITIONAL_LIBRARIES}")
        target_link_libraries(${full_target_name} PRIVATE ${arg_ADDITIONAL_LIBRARIES})
    endif()

else()
    message(STATUS "No main found for: ${full_target_name}")
endif()

endfunction()
