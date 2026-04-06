#define BOOST_TEST_MODULE Link_Queue_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Linear_Structure/Linear_Queue/Liner_Queue_Linked/Link_Queue.hpp"

BOOST_AUTO_TEST_SUITE(Queue)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Link_Queue_Behaviour)
{
    Run_Queue_Behaviour_Suite<Link_Queue<int>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
