if(BUILD_DEMOS)
    ds_add_cpp_demo(Sort_Demo "Sort" Sort/Demo.cpp)
    ds_add_cpp_demo(Sort_Quick_Demo "Sort_Quick" Sort/demo_quick.cpp)
endif()

if(BUILD_TESTING)
    ds_add_boost_unit_test(Sort_UnitTest "Sort" Sort/Unit_Test.cpp)
endif()
