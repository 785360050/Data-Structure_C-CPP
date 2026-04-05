#define BOOST_TEST_MODULE Sequential_List_Behaviour
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <initializer_list>
#include <stdexcept>

#include "../../Linear_Structure/Linear_List/Sequential_List/Sequential_List.hpp"

template <typename ListType>
void Check_Empty_State(ListType &list)
{
    BOOST_CHECK(list.Is_Empty());
    BOOST_CHECK_EQUAL(list.Get_Size(), 0U);
}

template <typename ListType>
void Check_Sequence(ListType &list, std::initializer_list<int> expected)
{
    BOOST_REQUIRE_EQUAL(list.Get_Size(), expected.size());

    size_t pos = 1;
    for (int value : expected)
        BOOST_CHECK_EQUAL(list[pos++], value);
}

template <typename ListType>
void Check_Default_Constructed_List()
{
    ListType list;

    Check_Empty_State(list);
    BOOST_CHECK_THROW(list[0], std::out_of_range);
    BOOST_CHECK_THROW(list[1], std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Delete(0), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Delete(1), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Update(0, 42), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Insert(0, 42), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Insert(2, 42), std::out_of_range);
}

template <typename ListType>
void Check_Insert_Update_Delete_Clear_Behaviour()
{
    ListType list;

    list.Element_Insert(1, 10);
    list.Element_Insert(2, 30);
    list.Element_Insert(2, 20);
    list.Element_Insert(1, 5);
    Check_Sequence(list, {5, 10, 20, 30});

    list.Element_Update(2, 11);
    BOOST_CHECK_EQUAL(list[2], 11);
    Check_Sequence(list, {5, 11, 20, 30});

    list.Element_Delete(3);
    Check_Sequence(list, {5, 11, 30});

    list.Element_Delete(1);
    Check_Sequence(list, {11, 30});

    list.List_Clear();
    Check_Empty_State(list);

    list.Element_Insert(1, 99);
    Check_Sequence(list, {99});
}

template <typename ListType>
void Check_Invalid_Positions_After_Populating()
{
    ListType list;
    list.Element_Insert(1, 1);
    list.Element_Insert(2, 2);
    list.Element_Insert(3, 3);

    BOOST_CHECK_THROW(list[0], std::out_of_range);
    BOOST_CHECK_THROW(list[4], std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Update(4, 4), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Delete(4), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Insert(5, 5), std::out_of_range);
}

template <typename ListType>
void Run_Behaviour_Suite()
{
    Check_Default_Constructed_List<ListType>();
    Check_Insert_Update_Delete_Clear_Behaviour<ListType>();
    Check_Invalid_Positions_After_Populating<ListType>();
}

BOOST_AUTO_TEST_SUITE(Sequential_List)
BOOST_AUTO_TEST_SUITE(Behaviour)

BOOST_AUTO_TEST_CASE(Sequential_List_Static_Behaviour)
{
    Run_Behaviour_Suite<Sequential_List_Static<int, 8>>();
}

BOOST_AUTO_TEST_CASE(Sequential_List_Dynamic_Behaviour)
{
    Run_Behaviour_Suite<Sequential_List_Dynamic<int>>();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
