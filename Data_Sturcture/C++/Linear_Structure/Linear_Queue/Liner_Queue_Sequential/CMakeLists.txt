add_library(ds_cpp_sequential_queue INTERFACE)
target_link_libraries(ds_cpp_sequential_queue INTERFACE ds_cpp_headers)

if(BUILD_DEMOS)
    ds_add_cpp_demo(Sequential_Queue_Demo "Sequential_Queue" Demo.cpp)
    target_link_libraries(Sequential_Queue_Demo PRIVATE ds_cpp_sequential_queue)
endif()
