

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Liner_Stack_Sequential/Liner_Stack_Sequential.h"


// g++ test.cpp -g -o test -lboost_unit_test_framework
BOOST_AUTO_TEST_CASE(Test1)
{
    Sequence_Stack<int> s(20); /// 空增栈
    // Sequence_Stack_Full_Ascending<char> s(5);///满增栈
    // Sequence_Stack_Empty_Decending<char> s(5);///空减栈
    // Sequence_Stack_Full_Decending<char> s(5);///满减栈

    BOOST_CHECK(s.Stack_GetLength() == 0);
    // s.Stack_Show("初始化5个单位的栈空间后：");
    for (int i = 0; i <= 10; i++)
        s.Element_Push(i);
    for (int i = 10; i <= 1;--i)
    {
        BOOST_CHECK(s.Stack_GetTop() == i);
        s.Element_Pop();
    }
    // s.Stack_Show("压入5个元素后：");
    // s.Stack_Clear();
    s.Stack_Show("出栈9个元素后");
    BOOST_CHECK(s.Stack_GetTop() == 0);
    BOOST_CHECK(s.Stack_GetLength() == 1);
    BOOST_CHECK(!s.Stack_CheckEmpty());

    // std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
    // std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
    // std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
    // while (s.Stack_GetLength() > 0)
    // {
    //     std::cout << s.Stack_GetTop() << "出栈" << std::endl;
    //     s.Element_Pop();
    // }

    // std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
}



