#define BOOST_TEST_MODULE Link_List_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Linear_Structure/Linear_List/Link_List/Link_List.hpp"

BOOST_AUTO_TEST_SUITE(Linear_List)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Link_List_Forward_Behaviour)
{
    Run_Linear_List_Behaviour_Suite<Link_List_Forward<int>>();
}

BOOST_AUTO_TEST_CASE(Link_List_Double_Behaviour)
{
    Run_Linear_List_Behaviour_Suite<Link_List_Double<int>>();
}

BOOST_AUTO_TEST_CASE(Link_List_Static_Behaviour)
{
    Run_Linear_List_Behaviour_Suite<Link_List_Static<int, 8>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
