#define BOOST_TEST_MODULE MergeFindSet_QuickFind_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Tree_Structure/MergeFindSet/MergeFindSet_QuickFind.hpp"

BOOST_AUTO_TEST_SUITE(MergeFindSet)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(QuickFind_Behaviour)
{
    Run_MergeFindSet_Behaviour_Suite<MergeFindSet_QuickFind<int>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
