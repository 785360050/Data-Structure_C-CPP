

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../Linear_Structure/Linear_Stack/Linear_Stack_Sequential/Linear_Stack_Sequential.h"

// g++ test.cpp -g -o test -lboost_unit_test_framework
BOOST_AUTO_TEST_SUITE(Stack)

BOOST_AUTO_TEST_CASE(EmptyStackTest)
{
    // 创建一个空的 Stack_ADT 实例
    Sequence_Stack<int> stack(5);

    // 在断言中验证栈是否为空
    BOOST_CHECK(stack.Stack_CheckEmpty());
    BOOST_CHECK_EQUAL(stack.Stack_GetLength(), 0);
}

BOOST_AUTO_TEST_CASE(PushPopTest)
{
    // 创建一个 Stack_ADT 实例
    Sequence_Stack<int> stack(20);

    // 向栈中添加元素
    stack.Element_Push(42);
    stack.Element_Push(17);

    // 验证栈的长度和栈顶元素
    BOOST_CHECK_EQUAL(stack.Stack_GetLength(), 2);
    BOOST_CHECK_EQUAL(stack.Stack_GetTop(), 17);

    // 出栈一个元素
    stack.Element_Pop();

    // 验证栈的长度和栈顶元素
    BOOST_CHECK_EQUAL(stack.Stack_GetLength(), 1);
    BOOST_CHECK_EQUAL(stack.Stack_GetTop(), 42);
}

BOOST_AUTO_TEST_SUITE_END()
