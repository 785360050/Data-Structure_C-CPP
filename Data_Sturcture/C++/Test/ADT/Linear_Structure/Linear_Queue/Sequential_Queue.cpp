#define BOOST_TEST_MODULE Sequential_Queue_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Linear_Structure/Linear_Queue/Liner_Queue_Sequential/Sequential_Queue.hpp"

BOOST_AUTO_TEST_SUITE(Queue)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Sequential_Queue_Redundancy_Behaviour)
{
    Run_Queue_Behaviour_Suite<Sequential_Queue_Redundancy<int, 8>>();
}

BOOST_AUTO_TEST_CASE(Sequential_Queue_Tag_Behaviour)
{
    Run_Queue_Behaviour_Suite<Sequential_Queue_Tag<int, 8>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
