add_library(ds_cpp_link_queue INTERFACE)
target_link_libraries(ds_cpp_link_queue INTERFACE ds_cpp_headers)

if(BUILD_DEMOS)
    ds_add_cpp_demo(Link_Queue_Demo "Link_Queue" Demo.cpp)
    target_link_libraries(Link_Queue_Demo PRIVATE ds_cpp_link_queue)
endif()
