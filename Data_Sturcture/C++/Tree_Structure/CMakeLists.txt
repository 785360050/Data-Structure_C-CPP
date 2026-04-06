add_library(ds_cpp_merge_find_set INTERFACE)
target_link_libraries(ds_cpp_merge_find_set INTERFACE ds_cpp_headers)

add_library(ds_cpp_tree_binary_search INTERFACE)
target_link_libraries(ds_cpp_tree_binary_search INTERFACE ds_cpp_headers)

add_library(ds_cpp_tree_binary INTERFACE)
target_link_libraries(ds_cpp_tree_binary INTERFACE ds_cpp_headers)

if(BUILD_DEMOS)
    ds_add_cpp_demo(Binary_Heap_Demo "Binary_Heap" Heap/main.cpp)
    ds_add_cpp_demo(Binary_Heap_STL_Demo "Binary_Heap_STL" Heap/ETC_Heap_With_STL/main.cpp)
    ds_add_cpp_demo(MergeFindSet_Demo "MergeFindSet" MergeFindSet/main.cpp)

    ds_add_cpp_demo(B_Tree_Demo "B_Tree" "Tree/HighOrder_Tree/B_Tree/main.cpp")
    ds_add_cpp_demo(HighOrder_Tree_Normal_Demo "HighOrder_Tree_Normal" "Tree/HighOrder_Tree/Normal Tree/main.cpp")
    ds_add_cpp_demo(HighOrder_Tree_Child_Demo "HighOrder_Tree_Child" "Tree/HighOrder_Tree/Normal Tree/Tree_HighOrder_Child/Demo.cpp")
    ds_add_cpp_demo(R_Tree_Demo "R_Tree" "Tree/HighOrder_Tree/R_Tree/main.cpp")

    ds_add_cpp_demo(Binary_Tree_Thread_Demo "Binary_Tree_Thread" "Tree/Tree_Binary/Binary_Tree_Thread/main.cpp")
    ds_add_cpp_demo(Binary_Tree_Normal_Demo "Binary_Tree_Normal" "Tree/Tree_Binary/Tree_Binary_Normal/main.cpp")

    if(BUILD_TREE_STRUCTURE_EXPERIMENTAL)
        ds_add_cpp_demo(B_Plus_Tree_Others_Demo "B_Plus_Tree_Others" "Tree/HighOrder_Tree/B_Tree/B_Plus_Others/main.cpp")
        ds_add_cpp_demo(Binary_Search_Tree_Demo "Binary_Search_Tree" "Tree/Tree_Binary/Tree_Binary_Search/main.cpp")
        ds_add_cpp_demo(Binary_Search_Tree_Normal_Demo "Binary_Search_Tree_Normal" "Tree/Tree_Binary/Tree_Binary_Search/Normal_Tree/main.cpp")
        ds_add_cpp_demo(AVL_Tree_Demo "AVL_Tree" "Tree/Tree_Binary/Tree_Binary_Search/AVL_Tree/main.cpp")
        ds_add_cpp_demo(AVL_Tree_Extra_Demo "AVL_Tree_Demo" "Tree/Tree_Binary/Tree_Binary_Search/AVL_Tree/Demo.cpp")
        ds_add_cpp_demo(Red_Black_Tree_Demo "Red_Black_Tree" "Tree/Tree_Binary/Tree_Binary_Search/Red_Black_Tree/main.cpp")
        ds_add_cpp_demo(Red_Black_Tree_Extra_Demo "Red_Black_Tree_Demo" "Tree/Tree_Binary/Tree_Binary_Search/Red_Black_Tree/Demo.cpp")
    else()
        message(STATUS "Experimental tree demos are disabled by default. Set BUILD_TREE_STRUCTURE_EXPERIMENTAL=ON to build the unfinished targets.")
    endif()
endif()
