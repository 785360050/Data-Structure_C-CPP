

#define BOOST_TEST_MODULE Link_List
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <limits>
#include <iostream>

#include "../../../../Linear_Structure/Linear_List/Link_List/Link_List.hpp"
#include "../../../../Test/Unit_Test/Test_Element.hpp"

// g++ Link_List.cpp -g -o Link_List -lboost_unit_test_framework -std=c++20
// valgrind --leak-check=full ./Link_List

template <typename List>
void test(const List &array, size_t size = 0, bool empty = true)
{
    BOOST_CHECK(array.Get_Size() == size);
    BOOST_CHECK(array.Is_Empty() == empty);
};

BOOST_AUTO_TEST_CASE(Con_Destruct_Copy)
{
    /// Link_List_Double
    Link_List_Forward<int> list;
    BOOST_CHECK(list.Get_Size() ==0);
    BOOST_CHECK(list.Get_Capcity()== 0);
    BOOST_CHECK(list.Is_Empty());
    std::initializer_list<int> initializer_list = {1, 2, 3, 4, 5};
    Link_List_Forward<int> list_initial{initializer_list};
    BOOST_CHECK(list_initial.Get_Size() == 5);
    BOOST_CHECK(list_initial.Get_Capcity() == 5);
    BOOST_CHECK(list_initial.Is_Empty() == false);
    for (size_t i = 0; i < initializer_list.size(); i++)
        list_initial[i + 1] = i;



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

    Link_List_Double<int> list_initial_doluble{initializer_list};
    test(list_initial_doluble, 5, false);
    for (size_t i = 0; i < initializer_list.size(); i++)
        list_initial_doluble[i + 1] = i;
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

    ///以下是不是动态测试做的
    
    // static_assert(  capcity > 0, "Capacity must be greater than 0");
    // listLink_List_Forward<Element<int>, 0> array0;

    // 错误：narrowing conversion of ‘-1’ from ‘int’ to ‘long unsigned int’ [-Wnarrowing]
    //  listLink_List_Forward<Element, -1> array1;
}

BOOST_AUTO_TEST_CASE(Operations_Static)
{

    Link_List_Forward<int> list;
    BOOST_CHECK_THROW(list.Element_Insert(0, 0), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Insert(2, 2), std::out_of_range);

    for (size_t i = 1; i <= 5; i++)
        list.Element_Insert(i, i);

    BOOST_CHECK(list.Get_Size() == 5);
    for (int i = 1; i <= 5; i++)
        BOOST_CHECK(list[i] == i);
    BOOST_CHECK_THROW(list[0], std::out_of_range);
    BOOST_CHECK_THROW(list[6], std::out_of_range);
    list.Element_Insert(1, 1);
    BOOST_CHECK(list[1]==1);

    list.Element_Update(1, 2);
    BOOST_CHECK(list.Get_Size() == 6);
    BOOST_CHECK(list[1] == 2);
    list.Element_Delete(1);
    BOOST_CHECK(list.Get_Size() == 5);
    BOOST_CHECK(list.Get_Capcity() == 5);

    list.List_Clear();
    BOOST_CHECK(list.Get_Size() == 0);
    BOOST_CHECK(list.Get_Capcity() == 0);
}

BOOST_AUTO_TEST_CASE(Operations_Dynamic)
{

    Link_List_Double<int> list;//初始化时不分配空间
    BOOST_CHECK_THROW(list.Element_Insert(0, 0), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Insert(2, 2), std::out_of_range);

    for (int i = 1; i <= 5; i++)
        list.Element_Insert(i, i);

    BOOST_CHECK(list.Get_Size() == 5);
    for (int i = 1; i <= 5; i++)
        BOOST_CHECK(list[i] == i);
    BOOST_CHECK_THROW(list[0], std::out_of_range);
    BOOST_CHECK_THROW(list[6], std::out_of_range);
    list.Element_Insert(1, 1);

    list.Element_Update(1, 2);
    BOOST_CHECK(list.Get_Size() == 6);
    BOOST_CHECK(list[1] == 2);
    list.Element_Delete(1);
    BOOST_CHECK(list.Get_Size() == 5);

    list.Element_Delete(list.Get_Size());
    BOOST_CHECK(list.Get_Size() == 4);
}

BOOST_AUTO_TEST_CASE(Operations_Dynamic_Element)
{

    Link_List_Double<Element<size_t>> list; // 初始化时不分配空间
    BOOST_CHECK_THROW(list.Element_Insert(0, {1,11}), std::out_of_range);
    BOOST_CHECK_THROW(list.Element_Insert(2, {2,22}), std::out_of_range);

    for (size_t i = 1; i <= 5; i++)
        list.Element_Insert(i, {i, 10 + i});

    BOOST_CHECK(list.Get_Size() == 5);
    for (size_t i = 1; i <= 5; i++)
        BOOST_CHECK(list[i] == Element<size_t>(i, 10 + i));
    BOOST_CHECK_THROW(list[0], std::out_of_range);
    BOOST_CHECK_THROW(list[6], std::out_of_range);
    list.Element_Insert(1, Element<size_t>(1, 10 + 1));

    list.Element_Update(1, Element<size_t>(2, 10 + 2));
    BOOST_CHECK(list.Get_Size() == 6);
    BOOST_CHECK(list[1] == Element<size_t>(2, 10 + 2));
    list.Element_Delete(1);
    BOOST_CHECK(list.Get_Size() == 5);

    list.Element_Delete(list.Get_Size());
    BOOST_CHECK(list.Get_Size() == 4);
}
