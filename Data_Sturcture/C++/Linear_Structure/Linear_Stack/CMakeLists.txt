add_subdirectory(Linear_Stack_Sequential)
add_subdirectory(Linear_Stack_Linked)

if(BUILD_DEMOS)
    ds_add_cpp_demo(Linear_Stack_Main_Demo "Linear_Stack" main.cpp)
endif()
