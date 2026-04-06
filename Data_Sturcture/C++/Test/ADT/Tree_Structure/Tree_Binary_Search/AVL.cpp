#define BOOST_TEST_MODULE Tree_Binary_Search_AVL_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/AVL_Tree/Tree_Binary_Search_AVL.hpp"

BOOST_AUTO_TEST_SUITE(Tree_Binary_Search_ADT)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(AVL_Behaviour)
{
    Run_Tree_Binary_Search_Behaviour_Suite<Storage::Tree_Binary_Search_AVL<int>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
