#define BOOST_TEST_MODULE Tree_Binary_Search_Red_Black_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/Red_Black_Tree/Tree_Binary_Search_BRT.hpp"

BOOST_AUTO_TEST_SUITE(Tree_Binary_Search_ADT)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Red_Black_Behaviour)
{
    Run_Tree_Binary_Search_Behaviour_Suite<Tree_Binary_Search_RBT<int>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
