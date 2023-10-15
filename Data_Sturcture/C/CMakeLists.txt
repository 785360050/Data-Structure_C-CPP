
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Definition Source_C)

add_executable(main main.cpp ${Source_C})

# target_link_libraries(main ${Source_C})