#pragma once

#include <exception>
#include <initializer_list>

template <typename StackType>
void Check_Stack_Empty_State(StackType &stack)
{
    BOOST_CHECK(stack.Is_Empty());
    BOOST_CHECK_EQUAL(stack.Get_Size(), 0U);
}

template <typename StackType, bool Check_Empty_Top = true>
void Check_Stack_Default_Constructed_Behaviour()
{
    StackType stack;

    Check_Stack_Empty_State(stack);
    BOOST_CHECK_THROW(stack.Element_Pop(), std::exception);
    if constexpr (Check_Empty_Top)
        BOOST_CHECK_THROW(stack.Get_Top(), std::exception);
}

template <typename StackType>
void Check_Stack_Lifo_Behaviour()
{
    StackType stack;

    stack.Element_Push(10);
    stack.Element_Push(20);
    stack.Element_Push(30);
    BOOST_CHECK_EQUAL(stack.Get_Size(), 3U);
    BOOST_CHECK_EQUAL(stack.Get_Top(), 30);

    stack.Element_Pop();
    BOOST_CHECK_EQUAL(stack.Get_Top(), 20);

    stack.Element_Push(40);
    BOOST_CHECK_EQUAL(stack.Get_Top(), 40);

    stack.Element_Pop();
    stack.Element_Pop();
    BOOST_CHECK_EQUAL(stack.Get_Top(), 10);
    stack.Element_Pop();

    Check_Stack_Empty_State(stack);
}

template <typename StackType>
void Check_Stack_Clear_Behaviour()
{
    StackType stack;

    stack.Element_Push(1);
    stack.Element_Push(2);
    stack.Element_Push(3);
    stack.Clear();

    Check_Stack_Empty_State(stack);

    stack.Element_Push(99);
    BOOST_CHECK_EQUAL(stack.Get_Top(), 99);
}

template <typename StackType, bool Check_Empty_Top = true>
void Run_Stack_Behaviour_Suite()
{
    Check_Stack_Default_Constructed_Behaviour<StackType, Check_Empty_Top>();
    Check_Stack_Lifo_Behaviour<StackType>();
    Check_Stack_Clear_Behaviour<StackType>();
}
