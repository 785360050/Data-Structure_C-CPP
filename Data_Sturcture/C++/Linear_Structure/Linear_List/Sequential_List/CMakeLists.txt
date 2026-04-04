
add_library(ds_cpp_sequential_list INTERFACE)
target_link_libraries(ds_cpp_sequential_list INTERFACE ds_cpp_headers)

if(BUILD_DEMOS)
    add_executable(Sequential_List_Demo Demo.cpp)
    target_link_libraries(Sequential_List_Demo PRIVATE ds_cpp_sequential_list)
    ds_configure_runtime_target(Sequential_List_Demo "Demo" "Sequential_List")

    if(MSVC) # VS热修复
      target_compile_options(Sequential_List_Demo PUBLIC "/ZI")
      target_link_options(Sequential_List_Demo PUBLIC "/INCREMENTAL")
    endif()
endif()

# set_property(Sequential_List_Demo 
#     output
# )
