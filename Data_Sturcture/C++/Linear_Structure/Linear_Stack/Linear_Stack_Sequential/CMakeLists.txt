add_library(ds_cpp_sequential_stack INTERFACE)
target_link_libraries(ds_cpp_sequential_stack INTERFACE ds_cpp_headers)

if(BUILD_DEMOS)
    ds_add_cpp_demo(Sequential_Stack_Demo "Sequential_Stack" Demo.cpp)
    target_link_libraries(Sequential_Stack_Demo PRIVATE ds_cpp_sequential_stack)
endif()
