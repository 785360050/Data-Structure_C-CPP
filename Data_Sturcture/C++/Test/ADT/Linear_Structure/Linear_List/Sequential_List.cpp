#define BOOST_TEST_MODULE Sequential_List_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Linear_Structure/Linear_List/Sequential_List/Sequential_List.hpp"

BOOST_AUTO_TEST_SUITE(Linear_List)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Sequential_List_Static_Behaviour)
{
    Run_Linear_List_Behaviour_Suite<Sequential_List_Static<int, 8>>();
}

BOOST_AUTO_TEST_CASE(Sequential_List_Dynamic_Behaviour)
{
    Run_Linear_List_Behaviour_Suite<Sequential_List_Dynamic<int>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
