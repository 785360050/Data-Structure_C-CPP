#define BOOST_TEST_MODULE Sequential_Stack_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Behaviour.hpp"
#include "Linear_Structure/Linear_Stack/Linear_Stack_Sequential/Sequential_Stack.hpp"

BOOST_AUTO_TEST_SUITE(Stack)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Empty_Ascending_Behaviour)
{
    Run_Stack_Behaviour_Suite<Sequential_Stack_Empty_Ascending<int, 8>>();
}

BOOST_AUTO_TEST_CASE(Empty_Descending_Behaviour)
{
    Run_Stack_Behaviour_Suite<Sequential_Stack_Empty_Descending<int, 8>>();
}

BOOST_AUTO_TEST_CASE(Full_Ascending_Behaviour)
{
    Run_Stack_Behaviour_Suite<Sequential_Stack_Full_Ascending<int, 8>>();
}

BOOST_AUTO_TEST_CASE(Full_Descending_Behaviour)
{
    Run_Stack_Behaviour_Suite<Sequential_Stack_Full_Descending<int, 8>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
