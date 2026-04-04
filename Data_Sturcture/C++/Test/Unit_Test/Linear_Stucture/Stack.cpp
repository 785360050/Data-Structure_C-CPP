

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../../../Linear_Structure/Linear_Stack/Linear_Stack_Sequential/Sequential_Stack.hpp"

// g++ test.cpp -g -o test -lboost_unit_test_framework
BOOST_AUTO_TEST_SUITE(Stack)

BOOST_AUTO_TEST_CASE(EmptyStackTest)
{
    Sequential_Stack<int, 5> stack;

    BOOST_CHECK(stack.Is_Empty());
    BOOST_CHECK_EQUAL(stack.Get_Size(), 0);
}

BOOST_AUTO_TEST_CASE(PushPopTest)
{
    Sequential_Stack<int, 20> stack;

    stack.Element_Push(42);
    stack.Element_Push(17);

    BOOST_CHECK_EQUAL(stack.Get_Size(), 2);
    BOOST_CHECK_EQUAL(stack.Get_Top(), 17);

    stack.Element_Pop();

    BOOST_CHECK_EQUAL(stack.Get_Size(), 1);
    BOOST_CHECK_EQUAL(stack.Get_Top(), 42);
}

BOOST_AUTO_TEST_SUITE_END()
