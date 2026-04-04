add_library(ds_cpp_link_stack INTERFACE)
target_link_libraries(ds_cpp_link_stack INTERFACE ds_cpp_headers)

if(BUILD_DEMOS)
    ds_add_cpp_demo(Link_Stack_Demo "Link_Stack" Demo.cpp)
    target_link_libraries(Link_Stack_Demo PRIVATE ds_cpp_link_stack)
endif()
