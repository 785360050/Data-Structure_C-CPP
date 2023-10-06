

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>

#include "Sequential_Stack.hpp"
#include "../../../Test/Unit_Test/Test_Element.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework -std=c++20

template <typename List>
void test(const List &list)
{
    BOOST_CHECK(list.Get_Size() == 0);
    BOOST_CHECK(list.Get_Capcity() == 0);
    BOOST_CHECK(list.Is_Empty());
};


BOOST_AUTO_TEST_CASE(Con_Destruct)
{
    /// Link_List_Double
    Sequence_Stack<int,5> stack;
    BOOST_CHECK(stack.Get_Size() ==0);
    BOOST_CHECK(stack.Get_Capcity()== 5);
    BOOST_CHECK(stack.Is_Empty());

    /// Link_List_Double
    

    Link_List_Double<int> list_doublelinked;
    test<Link_List_Double<int>>(list_doublelinked);

    auto array_copy_construct(list_doublelinked);
    test<Link_List_Double<int>>(array_copy_construct);
    auto array_copy_assign = list_doublelinked;
    test<Link_List_Double<int>>(array_copy_assign);

    auto array_move_construct(Link_List_Double<int>{});
    test<Link_List_Double<int>>(array_move_construct);
    auto array_move_assign = std::move(list_doublelinked);
    test<Link_List_Double<int>>(array_move_assign);
}

#include <vector>
BOOST_AUTO_TEST_CASE(Template_Parameter)
{
    Link_List_Forward<char> list;
    Link_List_Forward<const char *> array1;
    Link_List_Forward<int *> array2;
    Link_List_Forward<Element<int>> array3;
    Link_List_Forward<Element<char *> *> array4;
    Link_List_Forward<size_t> array5;

    array1.Element_Insert(1, "Hello");
    array1.Element_Insert(2, "World");
    array1.List_Clear();


}

BOOST_AUTO_TEST_CASE(Operations_Static)
{
    using ElementType = int;

    Sequence_Stack<char> s(5); /// 空增栈
    // Sequence_Stack_Full_Ascending<char> s(5);///满增栈
    // Sequence_Stack_Empty_Decending<char> s(5);///空减栈
    // Sequence_Stack_Full_Decending<char> s(5);///满减栈
    s.Stack_Show("初始化5个单位的栈空间后：");
    for (int i = 65; i < 70; i++)
        s.Element_Push(i);
    s.Stack_Show("压入5个元素后：");
    // s.Stack_Clear();
    std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
    std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
    std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
    while (s.Stack_GetLength() > 0)
    {
        std::cout << s.Stack_GetTop() << "出栈" << std::endl;
        s.Element_Pop();
    }

    std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
}


