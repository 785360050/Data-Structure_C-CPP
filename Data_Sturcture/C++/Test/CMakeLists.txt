add_executable(Sequential_List_UnitTest
    Unit_Test/Linear_Stucture/Linear_List/Sequential_List.cpp
)
target_link_libraries(Sequential_List_UnitTest
    PRIVATE
        ds_cpp_sequential_list
        Boost::unit_test_framework
)
ds_configure_runtime_target(Sequential_List_UnitTest "UnitTest" "Sequential_List")

add_test(NAME Sequential_List COMMAND Sequential_List_UnitTest)

add_executable(Sequential_List_Behaviour_UnitTest
    ADT/Linear_Structure/Linear_List/Sequential_List.cpp
)
target_link_libraries(Sequential_List_Behaviour_UnitTest
    PRIVATE
        ds_cpp_sequential_list
        Boost::unit_test_framework
)
ds_configure_runtime_target(Sequential_List_Behaviour_UnitTest "UnitTest" "Sequential_List_Behaviour")

add_test(NAME Sequential_List_Behaviour COMMAND Sequential_List_Behaviour_UnitTest)

add_executable(Link_List_Behaviour_UnitTest
    ADT/Linear_Structure/Linear_List/Link_List.cpp
)
target_link_libraries(Link_List_Behaviour_UnitTest
    PRIVATE
        ds_cpp_link_list
        Boost::unit_test_framework
)
ds_configure_runtime_target(Link_List_Behaviour_UnitTest "UnitTest" "Link_List_Behaviour")

add_test(NAME Link_List_Behaviour COMMAND Link_List_Behaviour_UnitTest)

add_executable(Sequential_List_Trace_Debug_Demo
    Linear_List/Sequential_List_Trace_Debug.cpp
)
target_link_libraries(Sequential_List_Trace_Debug_Demo
    PRIVATE
        ds_cpp_sequential_list
)
ds_configure_runtime_target(Sequential_List_Trace_Debug_Demo "Demo" "Sequential_List_Trace_Debug")

add_executable(Link_List_UnitTest
    Unit_Test/Linear_Stucture/Linear_List/Link_List.cpp
)
target_link_libraries(Link_List_UnitTest
    PRIVATE
        ds_cpp_link_list
        Boost::unit_test_framework
)
ds_configure_runtime_target(Link_List_UnitTest "UnitTest" "Link_List")

add_test(NAME Link_List COMMAND Link_List_UnitTest)

add_executable(Sequential_Stack_UnitTest
    Unit_Test/Linear_Stucture/Linear_Stack/Sequential_Stack.cpp
)
target_link_libraries(Sequential_Stack_UnitTest
    PRIVATE
        ds_cpp_sequential_stack
        Boost::unit_test_framework
)
ds_configure_runtime_target(Sequential_Stack_UnitTest "UnitTest" "Sequential_Stack")

add_test(NAME Sequential_Stack COMMAND Sequential_Stack_UnitTest)

add_executable(Sequential_Stack_Behaviour_UnitTest
    ADT/Linear_Structure/Linear_Stack/Sequential_Stack.cpp
)
target_link_libraries(Sequential_Stack_Behaviour_UnitTest
    PRIVATE
        ds_cpp_sequential_stack
        Boost::unit_test_framework
)
ds_configure_runtime_target(Sequential_Stack_Behaviour_UnitTest "UnitTest" "Sequential_Stack_Behaviour")

add_test(NAME Sequential_Stack_Behaviour COMMAND Sequential_Stack_Behaviour_UnitTest)

add_executable(Sequential_Queue_UnitTest
    Unit_Test/Linear_Stucture/Linear_Queue/Sequential_Queue.cpp
)
target_link_libraries(Sequential_Queue_UnitTest
    PRIVATE
        ds_cpp_sequential_queue
        Boost::unit_test_framework
)
ds_configure_runtime_target(Sequential_Queue_UnitTest "UnitTest" "Sequential_Queue")

add_test(NAME Sequential_Queue COMMAND Sequential_Queue_UnitTest)

add_executable(Sequential_Queue_Behaviour_UnitTest
    ADT/Linear_Structure/Linear_Queue/Sequential_Queue.cpp
)
target_link_libraries(Sequential_Queue_Behaviour_UnitTest
    PRIVATE
        ds_cpp_sequential_queue
        Boost::unit_test_framework
)
ds_configure_runtime_target(Sequential_Queue_Behaviour_UnitTest "UnitTest" "Sequential_Queue_Behaviour")

add_test(NAME Sequential_Queue_Behaviour COMMAND Sequential_Queue_Behaviour_UnitTest)

add_executable(Link_Queue_UnitTest
    Unit_Test/Linear_Stucture/Linear_Queue/Link_Queue.cpp
)
target_link_libraries(Link_Queue_UnitTest
    PRIVATE
        ds_cpp_link_queue
        Boost::unit_test_framework
)
ds_configure_runtime_target(Link_Queue_UnitTest "UnitTest" "Link_Queue")

add_test(NAME Link_Queue COMMAND Link_Queue_UnitTest)

add_executable(Link_Queue_Behaviour_UnitTest
    ADT/Linear_Structure/Linear_Queue/Link_Queue.cpp
)
target_link_libraries(Link_Queue_Behaviour_UnitTest
    PRIVATE
        ds_cpp_link_queue
        Boost::unit_test_framework
)
ds_configure_runtime_target(Link_Queue_Behaviour_UnitTest "UnitTest" "Link_Queue_Behaviour")

add_test(NAME Link_Queue_Behaviour COMMAND Link_Queue_Behaviour_UnitTest)

add_executable(Link_Stack_UnitTest
    Unit_Test/Linear_Stucture/Linear_Stack/Link_Stack.cpp
)
target_link_libraries(Link_Stack_UnitTest
    PRIVATE
        ds_cpp_link_stack
        Boost::unit_test_framework
)
ds_configure_runtime_target(Link_Stack_UnitTest "UnitTest" "Link_Stack")

add_test(NAME Link_Stack COMMAND Link_Stack_UnitTest)

add_executable(Link_Stack_Behaviour_UnitTest
    ADT/Linear_Structure/Linear_Stack/Link_Stack.cpp
)
target_link_libraries(Link_Stack_Behaviour_UnitTest
    PRIVATE
        ds_cpp_link_stack
        Boost::unit_test_framework
)
ds_configure_runtime_target(Link_Stack_Behaviour_UnitTest "UnitTest" "Link_Stack_Behaviour")

add_test(NAME Link_Stack_Behaviour COMMAND Link_Stack_Behaviour_UnitTest)

add_executable(Stack_Compatibility_UnitTest
    Unit_Test/Linear_Stucture/Stack.cpp
)
target_link_libraries(Stack_Compatibility_UnitTest
    PRIVATE
        ds_cpp_sequential_stack
        Boost::unit_test_framework
)
ds_configure_runtime_target(Stack_Compatibility_UnitTest "UnitTest" "Stack_Compatibility")

add_test(NAME Stack_Compatibility COMMAND Stack_Compatibility_UnitTest)

add_executable(Node_UnitTest
    Unit_Test/Node.cpp
)
target_link_libraries(Node_UnitTest
    PRIVATE
        ds_cpp_headers
        Boost::unit_test_framework
)
ds_configure_runtime_target(Node_UnitTest "UnitTest" "Node")

add_test(NAME Node COMMAND Node_UnitTest)

add_executable(Test_Element_UnitTest
    Unit_Test/Test_Element.cpp
)
target_link_libraries(Test_Element_UnitTest
    PRIVATE
        ds_cpp_headers
        Boost::unit_test_framework
)
ds_configure_runtime_target(Test_Element_UnitTest "UnitTest" "Test_Element")

add_test(NAME Test_Element COMMAND Test_Element_UnitTest)

add_executable(Binary_Heap_UnitTest
    Unit_Test/Tree_Structure/Binary_Heap.cpp
)
target_link_libraries(Binary_Heap_UnitTest
    PRIVATE
        ds_cpp_headers
        Boost::unit_test_framework
)
ds_configure_runtime_target(Binary_Heap_UnitTest "UnitTest" "Binary_Heap")

add_test(NAME Binary_Heap COMMAND Binary_Heap_UnitTest)

add_executable(MergeFindSet_QuickFind_Behaviour_UnitTest
    ADT/Tree_Structure/MergeFindSet/QuickFind.cpp
)
target_link_libraries(MergeFindSet_QuickFind_Behaviour_UnitTest
    PRIVATE
        ds_cpp_merge_find_set
        Boost::unit_test_framework
)
ds_configure_runtime_target(MergeFindSet_QuickFind_Behaviour_UnitTest "UnitTest" "MergeFindSet_QuickFind_Behaviour")

add_test(NAME MergeFindSet_QuickFind_Behaviour COMMAND MergeFindSet_QuickFind_Behaviour_UnitTest)

add_executable(MergeFindSet_QuickMerge_Behaviour_UnitTest
    ADT/Tree_Structure/MergeFindSet/QuickMerge.cpp
)
target_link_libraries(MergeFindSet_QuickMerge_Behaviour_UnitTest
    PRIVATE
        ds_cpp_merge_find_set
        Boost::unit_test_framework
)
ds_configure_runtime_target(MergeFindSet_QuickMerge_Behaviour_UnitTest "UnitTest" "MergeFindSet_QuickMerge_Behaviour")

add_test(NAME MergeFindSet_QuickMerge_Behaviour COMMAND MergeFindSet_QuickMerge_Behaviour_UnitTest)

add_executable(Tree_Binary_Search_Normal_Behaviour_UnitTest
    ADT/Tree_Structure/Tree_Binary_Search/Normal.cpp
)
target_link_libraries(Tree_Binary_Search_Normal_Behaviour_UnitTest
    PRIVATE
        ds_cpp_tree_binary_search
        Boost::unit_test_framework
)
ds_configure_runtime_target(Tree_Binary_Search_Normal_Behaviour_UnitTest "UnitTest" "Tree_Binary_Search_Normal_Behaviour")

add_test(NAME Tree_Binary_Search_Normal_Behaviour COMMAND Tree_Binary_Search_Normal_Behaviour_UnitTest)

add_executable(Tree_Binary_Search_AVL_Behaviour_UnitTest
    ADT/Tree_Structure/Tree_Binary_Search/AVL.cpp
)
target_link_libraries(Tree_Binary_Search_AVL_Behaviour_UnitTest
    PRIVATE
        ds_cpp_tree_binary_search
        Boost::unit_test_framework
)
ds_configure_runtime_target(Tree_Binary_Search_AVL_Behaviour_UnitTest "UnitTest" "Tree_Binary_Search_AVL_Behaviour")

add_test(NAME Tree_Binary_Search_AVL_Behaviour COMMAND Tree_Binary_Search_AVL_Behaviour_UnitTest)

add_executable(Tree_Binary_Search_Red_Black_Behaviour_UnitTest
    ADT/Tree_Structure/Tree_Binary_Search/Red_Black.cpp
)
target_link_libraries(Tree_Binary_Search_Red_Black_Behaviour_UnitTest
    PRIVATE
        ds_cpp_tree_binary_search
        Boost::unit_test_framework
)
ds_configure_runtime_target(Tree_Binary_Search_Red_Black_Behaviour_UnitTest "UnitTest" "Tree_Binary_Search_Red_Black_Behaviour")

add_test(NAME Tree_Binary_Search_Red_Black_Behaviour COMMAND Tree_Binary_Search_Red_Black_Behaviour_UnitTest)

add_executable(Tree_Binary_Normal_Behaviour_UnitTest
    ADT/Tree_Structure/Tree_Binary/Normal.cpp
)
target_link_libraries(Tree_Binary_Normal_Behaviour_UnitTest
    PRIVATE
        ds_cpp_tree_binary
        Boost::unit_test_framework
)
ds_configure_runtime_target(Tree_Binary_Normal_Behaviour_UnitTest "UnitTest" "Tree_Binary_Normal_Behaviour")

add_test(NAME Tree_Binary_Normal_Behaviour COMMAND Tree_Binary_Normal_Behaviour_UnitTest)

add_executable(Tree_Behaviour_UnitTest
    ADT/Tree_Structure/Tree/Tree.cpp
)
target_link_libraries(Tree_Behaviour_UnitTest
    PRIVATE
        ds_cpp_tree
        Boost::unit_test_framework
)
ds_configure_runtime_target(Tree_Behaviour_UnitTest "UnitTest" "Tree_Behaviour")

add_test(NAME Tree_Behaviour COMMAND Tree_Behaviour_UnitTest)

add_executable(Graph_AdjacencyList_Behaviour_UnitTest
    ADT/Graph_Structure/Graph_AdjacencyList.cpp
)
target_link_libraries(Graph_AdjacencyList_Behaviour_UnitTest
    PRIVATE
        ds_cpp_graph
        Boost::unit_test_framework
)
ds_configure_runtime_target(Graph_AdjacencyList_Behaviour_UnitTest "UnitTest" "Graph_AdjacencyList_Behaviour")

add_test(NAME Graph_AdjacencyList_Behaviour COMMAND Graph_AdjacencyList_Behaviour_UnitTest)

if(BUILD_DEMOS)
    ds_add_cpp_demo(Perfect_Forwarding_Demo "Perfect_Forwarding" "Unit_Test/完美转发案例.cpp")
endif()
