#define BOOST_TEST_MODULE Link_Stack_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Linear_Structure/Linear_Stack/Linear_Stack_Linked/Link_Stack.hpp"

BOOST_AUTO_TEST_SUITE(Stack)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Link_Stack_Behaviour)
{
    Run_Stack_Behaviour_Suite<Link_Stack<int>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
