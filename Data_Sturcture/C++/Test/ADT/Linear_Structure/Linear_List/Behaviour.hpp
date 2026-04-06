#pragma once

#include <exception>
#include <initializer_list>

template <typename ListType>
void Check_Linear_List_Empty_State(ListType &list)
{
    BOOST_CHECK(list.Is_Empty());
    BOOST_CHECK_EQUAL(list.Get_Size(), 0U);
}

template <typename ListType>
void Check_Linear_List_Sequence(ListType &list, std::initializer_list<int> expected)
{
    BOOST_REQUIRE_EQUAL(list.Get_Size(), expected.size());

    size_t pos = 1;
    for (int value : expected)
        BOOST_CHECK_EQUAL(list[pos++], value);
}

template <typename ListType>
void Check_Linear_List_Default_Constructed_Behaviour()
{
    ListType list;

    Check_Linear_List_Empty_State(list);
    BOOST_CHECK_THROW(list[0], std::exception);
    BOOST_CHECK_THROW(list[1], std::exception);
    BOOST_CHECK_THROW(list.Element_Delete(0), std::exception);
    BOOST_CHECK_THROW(list.Element_Delete(1), std::exception);
    BOOST_CHECK_THROW(list.Element_Update(0, 42), std::exception);
    BOOST_CHECK_THROW(list.Element_Update(1, 42), std::exception);
    BOOST_CHECK_THROW(list.Element_Insert(0, 42), std::exception);
    BOOST_CHECK_THROW(list.Element_Insert(2, 42), std::exception);
}

template <typename ListType>
void Check_Linear_List_Insert_Update_Delete_Clear_Behaviour()
{
    ListType list;

    list.Element_Insert(1, 10);
    list.Element_Insert(2, 30);
    list.Element_Insert(2, 20);
    list.Element_Insert(1, 5);
    Check_Linear_List_Sequence(list, {5, 10, 20, 30});

    list.Element_Update(2, 11);
    Check_Linear_List_Sequence(list, {5, 11, 20, 30});

    list.Element_Delete(3);
    Check_Linear_List_Sequence(list, {5, 11, 30});

    list.Element_Delete(1);
    Check_Linear_List_Sequence(list, {11, 30});

    list.List_Clear();
    Check_Linear_List_Empty_State(list);

    list.Element_Insert(1, 99);
    Check_Linear_List_Sequence(list, {99});
}

template <typename ListType>
void Check_Linear_List_Invalid_Positions_After_Populating()
{
    ListType list;
    list.Element_Insert(1, 1);
    list.Element_Insert(2, 2);
    list.Element_Insert(3, 3);

    BOOST_CHECK_THROW(list[0], std::exception);
    BOOST_CHECK_THROW(list[4], std::exception);
    BOOST_CHECK_THROW(list.Element_Update(0, 4), std::exception);
    BOOST_CHECK_THROW(list.Element_Update(4, 4), std::exception);
    BOOST_CHECK_THROW(list.Element_Delete(0), std::exception);
    BOOST_CHECK_THROW(list.Element_Delete(4), std::exception);
    BOOST_CHECK_THROW(list.Element_Insert(5, 5), std::exception);
}

template <typename ListType>
void Run_Linear_List_Behaviour_Suite()
{
    Check_Linear_List_Default_Constructed_Behaviour<ListType>();
    Check_Linear_List_Insert_Update_Delete_Clear_Behaviour<ListType>();
    Check_Linear_List_Invalid_Positions_After_Populating<ListType>();
}
