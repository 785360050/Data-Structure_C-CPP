
add_library(ds_cpp_link_list INTERFACE)
target_link_libraries(ds_cpp_link_list INTERFACE ds_cpp_headers)

if(BUILD_DEMOS)
    add_executable(Link_List_Demo Demo.cpp)
    target_link_libraries(Link_List_Demo PRIVATE ds_cpp_link_list)
    ds_configure_runtime_target(Link_List_Demo "Demo" "Link_List")

    if(MSVC) # VS热修复
      target_compile_options(Link_List_Demo PUBLIC "/ZI")
      target_link_options(Link_List_Demo PUBLIC "/INCREMENTAL")
    endif()
endif()

# set_property(Link_List_Demo 
#     output
# )
