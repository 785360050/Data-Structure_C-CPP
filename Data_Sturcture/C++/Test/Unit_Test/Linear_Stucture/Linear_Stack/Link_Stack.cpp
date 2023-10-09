

#define BOOST_TEST_MODULE Link_Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <limits>
#include <iostream>
#include <list>

#include "../../../../Linear_Structure/Linear_Stack/Linear_Stack_Linked/Link_Stack.hpp"

#include "../../../../Test/Unit_Test/Test_Element.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework -std=c++20

void test(const Link_Stack<int> &stack, size_t size = 0,  bool empty = true)
{
    BOOST_CHECK(stack.Get_Size() == size);
    BOOST_CHECK(stack.Is_Empty() == empty);
};


BOOST_AUTO_TEST_CASE(Con_Destruct)
{
    { // Sequential_Queue_Redundancy

        Link_Stack<int> stack;
        test(stack, 0);

        auto stack_copy_construct(stack);
        test(stack_copy_construct, 0);
        auto stack_copy_assign = stack;
        test(stack_copy_assign, 0);

        auto stack_move_construct(Link_Stack<int>{});
        test(stack_move_construct, 0);
        auto stack_move_assign = std::move(stack);
        test(stack_move_assign, 0);
    }

}

BOOST_AUTO_TEST_CASE(Template_Parameter)
{
    Link_Stack<char> stack;
    Link_Stack<const char *> stack1;
    Link_Stack<int *> stack2;
    Link_Stack<Element<int>> stack3;
    Link_Stack<Element<char *> *> stack4;
    Link_Stack<size_t> stack5;

    stack1.Element_Push("Hello");
    stack1.Element_Push("World");
    stack1.Clear();

}

BOOST_AUTO_TEST_CASE(Operations)
{
    Link_Stack<int> stack;

    for (int i = 1; i <= 5; i++)
        stack.Element_Push(i);

    BOOST_CHECK(stack.Get_Size() == 5);

    for (int i = 5; i >= 1; i--)
    {
        BOOST_CHECK(stack.Get_Top() == i);
        stack.Element_Pop();
    }
    BOOST_CHECK(stack.Get_Size() == 0);
    BOOST_CHECK(stack.Is_Empty());

    // static_assert(std::is_pointer<int>::value == std::false_type());
    stack.Clear();
    BOOST_CHECK(stack.Get_Size() == 0);

}

BOOST_AUTO_TEST_CASE(Operations_With_Element)
{
    using ElementType = Element<size_t>;

    Link_Stack<ElementType> stack;

    for (size_t i = 1; i <= 5; i++)
        stack.Element_Push({i,i});

    BOOST_CHECK(stack.Get_Size() == 5);

    for (size_t i = 5;i>=1; i--)
    {
        BOOST_CHECK(stack.Get_Top() == ElementType(i, i));
        stack.Element_Pop();
    }
    BOOST_CHECK(stack.Get_Size() == 0);
    BOOST_CHECK(stack.Is_Empty());

    // static_assert(std::is_pointer<int>::value == std::false_type());
    stack.Clear();
    BOOST_CHECK(stack.Get_Size() == 0);
}

template <typename StackType>
void Prepare_Element(StackType &stack, std::initializer_list<int> list)
{
    // BOOST_REQUIRE_GE(5, list.size());
    for (auto &e : list)
        stack.Element_Push(e);
};
template <typename StackType>
void Check_Element(StackType stack, std::initializer_list<int> list)
{
    // BOOST_REQUIRE_EQUAL(stack.Get_Size(), list.size());

    for (auto &e : list)
    {
        BOOST_CHECK(stack.Get_Top() == e);
        stack.Element_Pop();
    }
};
BOOST_AUTO_TEST_CASE(Copy_Control)
{

    {
        Link_Stack<int> stack;
        test(stack, 0);
        std::initializer_list<int> list{1, 2, 3, 4, 5};
        std::initializer_list<int> list_reverse {5, 4, 3, 2, 1};
        Prepare_Element<Link_Stack<int>>(stack, list);
        Check_Element<Link_Stack<int>>(stack, list_reverse);

        auto stack_copy_construct(stack);
        test(stack_copy_construct, 5, false);
        Check_Element<Link_Stack<int>>(stack_copy_construct, list_reverse);
        auto stack_copy_assign = stack;
        test(stack_copy_assign, 5, false);
        Check_Element<Link_Stack<int>>(stack_copy_assign, list_reverse);

        auto stack_move_construct(std::move(stack));
        test(stack_move_construct, 5, false);
        test(stack, 0, 6);
        Check_Element<Link_Stack<int>>(stack_move_construct, list_reverse);
        auto stack_move_assign = std::move(stack_move_construct);
        test(stack_move_assign, 5, false);
        test(stack_move_construct, 0, 6);
        Check_Element<Link_Stack<int>>(stack_move_assign, list_reverse);
    }
}
