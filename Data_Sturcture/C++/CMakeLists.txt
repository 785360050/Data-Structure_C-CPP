add_library(ds_cpp_headers INTERFACE)
target_include_directories(ds_cpp_headers
    INTERFACE
        ${PROJECT_SOURCE_DIR}/Data_Sturcture/C++
)

option(BUILD_ALGORITHMS "Build C++ algorithms targets" ON)
option(BUILD_GRAPH_STRUCTURE "Build C++ graph structure targets" OFF)
option(BUILD_SET_STRUCTURE "Build C++ set structure targets" ON)
option(BUILD_TREE_STRUCTURE "Build C++ tree structure targets" OFF)
option(BUILD_GRAPH_STRUCTURE_EXPERIMENTAL "Build experimental graph structure demo targets" OFF)
option(BUILD_TREE_STRUCTURE_EXPERIMENTAL "Build experimental tree structure demo targets" OFF)

if(BUILD_TESTING)
    find_package(Boost REQUIRED COMPONENTS unit_test_framework)
endif()

add_subdirectory(Linear_Structure)

if(BUILD_ALGORITHMS)
    add_subdirectory(Algorithms)
endif()

if(BUILD_GRAPH_STRUCTURE)
    add_subdirectory(Graph_Structure)
endif()

if(BUILD_SET_STRUCTURE)
    add_subdirectory(Set_Structure)
endif()

if(BUILD_TREE_STRUCTURE)
    add_subdirectory(Tree_Structure)
endif()

if(BUILD_TESTING)
    add_subdirectory(Test)
endif()
