function(ds_configure_runtime_target target category output_name)
    if(category STREQUAL "Demo")
        set(output_dir "${DS_OUTPUT_DIR_DEMO}")
    elseif(category STREQUAL "UnitTest")
        set(output_dir "${DS_OUTPUT_DIR_UNIT_TEST}")
    elseif(category STREQUAL "Reference")
        set(output_dir "${DS_OUTPUT_DIR_REFERENCE}")
    else()
        message(FATAL_ERROR "Unknown runtime target category: ${category}")
    endif()

    set_target_properties(${target} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${output_dir}"
        OUTPUT_NAME "${output_name}"
    )
endfunction()

function(ds_add_cpp_demo target output_name source)
    add_executable(${target} "${source}")
    target_link_libraries(${target} PRIVATE ds_cpp_headers)
    ds_configure_runtime_target(${target} "Demo" "${output_name}")

    if(MSVC)
        target_compile_options(${target} PUBLIC "/ZI")
        target_link_options(${target} PUBLIC "/INCREMENTAL")
    endif()
endfunction()

function(ds_add_boost_unit_test target output_name source)
    add_executable(${target} "${source}")
    target_link_libraries(${target} PRIVATE ds_cpp_headers Boost::unit_test_framework)
    ds_configure_runtime_target(${target} "UnitTest" "${output_name}")
    add_test(NAME "${output_name}" COMMAND ${target})
endfunction()
