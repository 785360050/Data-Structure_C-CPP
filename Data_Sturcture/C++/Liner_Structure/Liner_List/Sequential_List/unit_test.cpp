

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <limits>
#include <iostream>

#include "Sequential_List.hpp"
#include "../../../Test/Unit_Test/Test_Element.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework -std=c++20

BOOST_AUTO_TEST_CASE(Con_Destruct_Copy)
{
    /// Sequential_List_Dynamic
    Sequential_List_Static<int, 5> array_static;
    BOOST_CHECK(array_static.Get_Size() == 0);
    BOOST_CHECK(array_static.Get_Capcity() == 5);
    BOOST_CHECK(array_static.Is_Empty());

    /// Sequential_List_Dynamic
    auto test = [](const Sequential_List_Dynamic<int> &array)
    {
        BOOST_CHECK(array.Get_Size() == 0);
        BOOST_CHECK(array.Get_Capcity() == 0);
        BOOST_CHECK(array.Is_Empty());
    };

    Sequential_List_Dynamic<int> array_dynamic;
    test(array_dynamic);

    auto array_copy_construct(array_dynamic);
    test(array_copy_construct);
    auto array_copy_assign = array_dynamic;
    test(array_copy_assign);

    auto array_move_construct(Sequential_List_Dynamic<int>{});
    test(array_move_construct);
    auto array_move_assign = std::move(array_dynamic);
    test(array_move_assign);
}

BOOST_AUTO_TEST_CASE(Template_Parameter)
{
    Sequential_List_Static<char, 5> array;
    Sequential_List_Static<const char *, 5> array1;
    Sequential_List_Static<int *, 5> array2;
    Sequential_List_Static<Element<int>, 5> array3;
    Sequential_List_Static<Element<char *> *, 5> array4;
    Sequential_List_Static<size_t, 5> array5;

    array1.Element_Insert(1, "Hello");
    array1.Element_Insert(2, "World");
    array1.List_Clear();

// //暂时先限制元素类型为非指针类型
//     Sequential_List_Static<Element<int> *, 5> clear_pointer;
//     for (int i = 1; i <= 5; i++)
//         clear_pointer.Element_Insert(i, new Element(i,10+i));

//     clear_pointer.List_Clear();

    ///以下是不是动态测试做的
    
    // static_assert(  capcity > 0, "Capacity must be greater than 0");
    // Sequential_List_Static<Element<int>, 0> array0;

    // 错误：narrowing conversion of ‘-1’ from ‘int’ to ‘long unsigned int’ [-Wnarrowing]
    //  Sequential_List_Static<Element, -1> array1;
}

BOOST_AUTO_TEST_CASE(Operations_Static)
{
    using ElementType = int;

    Sequential_List_Static<int, 5> array_static;
    BOOST_CHECK_THROW(array_static.Element_Insert(0, 0), std::out_of_range);
    BOOST_CHECK_THROW(array_static.Element_Insert(2, 2), std::out_of_range);

    for (size_t i = 1; i <= 5; i++)
        array_static.Element_Insert(i, i);

    BOOST_CHECK(array_static.Get_Size() == 5);
    for (size_t i = 1; i <= 5; i++)
        BOOST_CHECK(array_static[i] == i);
    BOOST_CHECK_THROW(array_static[0], std::out_of_range);
    BOOST_CHECK_THROW(array_static[6], std::out_of_range);
    BOOST_CHECK_THROW(array_static.Element_Insert(1, 1), std::runtime_error);

    array_static.Element_Update(1, 2);
    BOOST_CHECK(array_static.Get_Size() == 5);
    BOOST_CHECK(array_static[1] == 2);
    array_static.Element_Delete(1);
    BOOST_CHECK(array_static.Get_Size() == 4);
    BOOST_CHECK(array_static.Get_Capcity() == 5);

    static_assert(std::is_pointer<int>::value==std::false_type());
    array_static.List_Clear();
    BOOST_CHECK(array_static.Get_Size() == 0);
    BOOST_CHECK(array_static.Get_Capcity()==5);
}

BOOST_AUTO_TEST_CASE(Operations_Dynamic)
{

    Sequential_List_Dynamic<int> array_dynamic(1);//初始化时不分配空间
    BOOST_CHECK_THROW(array_dynamic.Element_Insert(0, 0), std::out_of_range);
    BOOST_CHECK_THROW(array_dynamic.Element_Insert(2, 2), std::out_of_range);

    for (size_t i = 1; i <= 5; i++)
        array_dynamic.Element_Insert(i, i);
    BOOST_CHECK(array_dynamic.Get_Capcity()==8);//1->2->4->8

    BOOST_CHECK(array_dynamic.Get_Size() == 5);
    for (size_t i = 1; i <= 5; i++)
        BOOST_CHECK(array_dynamic[i] == i);
    BOOST_CHECK_THROW(array_dynamic[0], std::out_of_range);
    BOOST_CHECK_THROW(array_dynamic[6], std::out_of_range);
    array_dynamic.Element_Insert(1, 1);


    array_dynamic.Element_Update(1, 2);
    BOOST_CHECK(array_dynamic.Get_Size() == 6);
    BOOST_CHECK(array_dynamic[1] == 2);
    array_dynamic.Element_Delete(1);
    BOOST_CHECK(array_dynamic.Get_Size() == 5);
    BOOST_CHECK(array_dynamic.Get_Capcity() == 8);

    array_dynamic.Element_Delete(array_dynamic.Get_Size());
    BOOST_CHECK(array_dynamic.Get_Size() == 4);
    BOOST_CHECK(array_dynamic.Get_Capcity() == 4);
}


BOOST_AUTO_TEST_CASE(Operations_Dynamic_Element)
{
    Sequential_List_Dynamic<Element<size_t>> array_dynamic(1); // 初始化时不分配空间
    // Sequential_List_Dynamic<Element<size_t>> array_dynamic(5); // 初始化时不分配空间
    BOOST_CHECK_THROW(array_dynamic.Element_Insert(0, {1, 11}), std::out_of_range);
    BOOST_CHECK_THROW(array_dynamic.Element_Insert(2, {2,22}), std::out_of_range);

    for (size_t i = 1; i <= 5; i++)
        array_dynamic.Element_Insert(i, {i, 10 + i});
    BOOST_CHECK(array_dynamic.Get_Capcity()==8);//1->2->4->8

    BOOST_CHECK(array_dynamic.Get_Size() == 5);
    for (size_t i = 1; i <= 5; i++)
        BOOST_CHECK(array_dynamic[i] == Element<size_t>(i, 10 + i));
    BOOST_CHECK_THROW(array_dynamic[0], std::out_of_range);
    BOOST_CHECK_THROW(array_dynamic[6], std::out_of_range);
    array_dynamic.Element_Insert(1, Element<size_t>(1, 10 + 1));

    array_dynamic.Element_Update(1, Element<size_t>(2, 10 + 2));
    BOOST_CHECK(array_dynamic.Get_Size() == 6);
    BOOST_CHECK(array_dynamic[1] == Element<size_t>(2, 10 + 2));
    // array_dynamic.List_Show("");
    array_dynamic.Element_Delete(1);
    BOOST_CHECK(array_dynamic.Get_Size() == 5);
    BOOST_CHECK(array_dynamic.Get_Capcity() == 8);

    array_dynamic.Element_Delete(array_dynamic.Get_Size());
    BOOST_CHECK(array_dynamic.Get_Size() == 4);
    BOOST_CHECK(array_dynamic.Get_Capcity() == 4);
}

