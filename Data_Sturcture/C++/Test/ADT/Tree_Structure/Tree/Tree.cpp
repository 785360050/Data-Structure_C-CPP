#define BOOST_TEST_MODULE Tree_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"

BOOST_AUTO_TEST_SUITE(Tree)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Current_Implementation_Blocker)
{
    Report_Tree_Behaviour_Blocker();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
