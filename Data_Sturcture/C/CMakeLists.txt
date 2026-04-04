aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Definition Source_C)

add_executable(C_Reference main.cpp ${Source_C})

ds_configure_runtime_target(C_Reference "Reference" "Data_Structure_C")

# target_link_libraries(C_Reference ${Source_C})
