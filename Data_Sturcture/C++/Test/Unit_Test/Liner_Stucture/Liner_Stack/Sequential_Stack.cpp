

#define BOOST_TEST_MODULE Sequential_Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <limits>
#include <iostream>
#include <list>

#include "../../../../Liner_Structure/Liner_Stack/Liner_Stack_Sequential/Sequential_Stack.hpp"

#include "../../../../Test/Unit_Test/Test_Element.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework -std=c++20

template <typename StackType>
void test(const StackType &stack, size_t size = 0, bool empty = true)
{
    BOOST_CHECK(stack.Get_Size() == size);
    BOOST_CHECK(stack.Is_Empty() == empty);
};

template <typename StackType>
void _Con_Destruct()
{
    StackType stack;
    test(stack, 0);

    auto stack_copy_construct(stack);
    test(stack_copy_construct, 0);
    auto stack_copy_assign = stack;
    test(stack_copy_assign, 0);

    auto stack_move_construct(StackType{});
    test(stack_move_construct, 0);
    auto stack_move_assign = std::move(stack);
    test(stack_move_assign, 0);
}

BOOST_AUTO_TEST_CASE(Con_Destruct)
{
    _Con_Destruct<Sequential_Stack_Empty_Ascending  <int,5>>();
    _Con_Destruct<Sequential_Stack_Empty_Descending <int,5>>();
    _Con_Destruct<Sequential_Stack_Full_Ascending   <int,5>>();
    _Con_Destruct<Sequential_Stack_Full_Descending  <int,5>>();
}

template <typename StackType>
void _Operations()
{
    using ElementType = int;

    StackType stack;

    for (size_t i = 1; i <= 5; i++)
        stack.Element_Push(i);

    BOOST_CHECK_THROW(stack.Element_Push(0), std::out_of_range);
    test(stack, 5, false);

    for (size_t i = 5; i >= 1; i--)
    {
        BOOST_CHECK(stack.Get_Top() == i);
        stack.Element_Pop();
    }
    BOOST_CHECK_THROW(stack.Element_Pop(), std::out_of_range);
    test(stack, 0);
    // static_assert(std::is_pointer<int>::value == std::false_type());
    stack.Clear();
    test(stack, 0);
}

BOOST_AUTO_TEST_CASE(Operations)
{
    _Operations<Sequential_Stack_Empty_Ascending  <int,5>>();
    _Operations<Sequential_Stack_Empty_Descending <int,5>>();
    _Operations<Sequential_Stack_Full_Ascending   <int,5>>();
    _Operations<Sequential_Stack_Full_Descending  <int,5>>();
}

template <typename StackType>
void _Operations_With_Element()
{
    using ElementType = Element<size_t>;

    Sequential_Stack<ElementType, 5> stack;

    for (size_t i = 1; i <= 5; i++)
        stack.Element_Push({i, i});

    BOOST_CHECK(stack.Get_Size() == 5);

    for (size_t i = 5; i >= 1; i--)
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

BOOST_AUTO_TEST_CASE(Operations_With_Element)
{
    _Operations_With_Element<Sequential_Stack_Empty_Ascending<int, 5>>();
    _Operations_With_Element<Sequential_Stack_Empty_Descending<int, 5>>();
    _Operations_With_Element<Sequential_Stack_Full_Ascending<int, 5>>();
    _Operations_With_Element<Sequential_Stack_Full_Descending<int, 5>>();
}

template <typename StackType>
void Prepare_Element(StackType &stack, std::initializer_list<int> list)
{
    for (auto &e : list)
        stack.Element_Push(e);
};
template <typename StackType>
void Check_Element(StackType stack, std::initializer_list<int> list)
{
    for (auto &e : list)
    {
        BOOST_CHECK(stack.Get_Top() == e);
        stack.Element_Pop();
    }
};
template <typename StackType>
void _Copy_Control()
{
    StackType stack;
    test(stack, 0);
    std::initializer_list<int> list{1, 2, 3, 4, 5};
    std::initializer_list<int> list_reverse{5, 4, 3, 2, 1};
    Prepare_Element<StackType>(stack, list);
    Check_Element<StackType>(stack, list_reverse);

    auto stack_copy_construct(stack);
    test(stack_copy_construct, 5, false);
    Check_Element<StackType>(stack_copy_construct, list_reverse);
    auto stack_copy_assign = stack;
    test(stack_copy_assign, 5, false);
    Check_Element<StackType>(stack_copy_assign, list_reverse);

    auto stack_move_construct(std::move(stack));
    test(stack_move_construct, 5, false);
    test(stack, 0);
    Check_Element<StackType>(stack_move_construct, list_reverse);
    auto stack_move_assign = std::move(stack_move_construct);
    test(stack_move_assign, 5, false);
    test(stack_move_construct, 0);
    Check_Element<StackType>(stack_move_assign, list_reverse);
}
BOOST_AUTO_TEST_CASE(Copy_Control)
{

    _Copy_Control<Sequential_Stack_Empty_Ascending<int, 5>>();
    _Copy_Control<Sequential_Stack_Empty_Descending<int, 5>>();
    _Copy_Control<Sequential_Stack_Full_Ascending<int, 5>>();
    _Copy_Control<Sequential_Stack_Full_Descending<int, 5>>();
}
