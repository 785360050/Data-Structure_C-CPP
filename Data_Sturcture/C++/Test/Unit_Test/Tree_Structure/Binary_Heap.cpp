

#define BOOST_TEST_MODULE Binary_Heap
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <limits>
#include <iostream>
#include <list>

#include "../../../Tree_Structure/Heap/Binary_Heap.hpp"

#include "../Test_Element.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework -std=c++20


template <typename Binary_Heap>
void test(const Binary_Heap &heap, size_t size = 0, bool empty = true)
{
    BOOST_CHECK(heap.Get_Size() == size);
    BOOST_CHECK(heap.Is_Empty() == empty);
};

#include <vector>
/// @brief 检查是否为按对应比较方式的堆，O(n)的空间复杂度
template <typename Binary_Heap, typename ElementType, typename Compare>
void Check(Binary_Heap heap)
{
    BOOST_CHECK(heap.Check_Heap());
}

BOOST_AUTO_TEST_CASE(Con_Destruct)
{
    { // Sequential_Queue_Redundancy

        Binary_Heap<int, 5> heap;
        test(heap, 0);

        auto heap_copy_construct(heap);
        test(heap_copy_construct, 0);
        auto heap_copy_assign = heap;
        test(heap_copy_assign, 0);

        auto heap_move_construct(Binary_Heap<int, 5>{});
        test(heap_move_construct, 0);
        auto heap_move_assign = std::move(heap);
        test(heap_move_assign, 0);
    }
    // initializer list
    Binary_Heap<int, 5> heap{5, 4, 3, 2, 1};
    test(heap, 5, false);
    Check<decltype(heap), int, std::less<>>(heap);
}

BOOST_AUTO_TEST_CASE(Template_Parameter)
{
    Binary_Heap<char, 5> heap;
    Binary_Heap<const char *, 5> stack1;
    Binary_Heap<int *, 5> stack2;
    Binary_Heap<Element<int>, 5> stack3;
    Binary_Heap<Element<char *> *, 5> stack4;
    Binary_Heap<size_t, 5> stack5;

    stack1.Push("Hello");
    stack1.Push("World");
    stack1.Clear();
    test(stack1, 0);
}

BOOST_AUTO_TEST_CASE(Operations)
{
    { // 小根堆
        Binary_Heap<int, 5> heap_min;
        BOOST_CHECK(heap_min.Get_Size() == 0);
        BOOST_CHECK(heap_min.Is_Empty());

        for (int i = 0; i < 5; i++)
        {
            heap_min.Push(i);
            BOOST_CHECK(heap_min.Get_Top() == 0);
        }
        Check<decltype(heap_min), int, std::less<>>(heap_min);
        BOOST_CHECK_THROW(heap_min.Push(0), std::runtime_error);

        for (int i = 0; i < 5; i++)
        {
            heap_min.Pop();
            Check<decltype(heap_min), int, std::less<>>(heap_min);
        }
        BOOST_CHECK_THROW(heap_min.Pop(), std::runtime_error);
    }

    { // 大根堆
        Binary_Heap<int, 5, std::greater<>> heap_max;
        for (int i = 0; i < 5; i++)
        {
            heap_max.Push(i);
            BOOST_CHECK(heap_max.Get_Top() == i);
        }
        Check<decltype(heap_max), int, std::greater<>>(heap_max);
        BOOST_CHECK_THROW(heap_max.Push(0), std::runtime_error);

        for (int i = 0; i < 5; i++)
        {
            heap_max.Pop();
            Check<decltype(heap_max), int, std::greater<>>(heap_max);
        }
        BOOST_CHECK_THROW(heap_max.Pop(), std::runtime_error);
    }
}

BOOST_AUTO_TEST_CASE(Operations_With_Element)
{
    using ElementType = Element<size_t>;

    Binary_Heap<ElementType, 5> heap;

    for (size_t i = 0; i < 5; i++)
    {
        Element elemenet(i, i);
        heap.Push(std::move(elemenet));
        Check<decltype(heap), int, std::less<>>(heap);
    }
    Check<decltype(heap), int, std::less<>>(heap);
    BOOST_CHECK_THROW(heap.Push({0, 0}), std::runtime_error);

    for (int i = 0; i < 5; i++)
    {
        heap.Pop();
        Check<decltype(heap), int, std::less<>>(heap);
    }
    BOOST_CHECK_THROW(heap.Pop(), std::runtime_error);
}


BOOST_AUTO_TEST_CASE(Copy_Control)
{

    using Binary_Heap=Binary_Heap<int, 5, std::greater<>>;

    std::initializer_list<int> list{1, 2, 3, 4, 5};
    Binary_Heap heap{list}, heap_copy{list}, heap_move{list};
    test(heap, 5, false);
    BOOST_CHECK((Binary_Heap{heap} == heap_copy));

    Binary_Heap heap_move_construct{std::move(heap)};
    test(heap, 0);
    test(heap_move_construct, 5, false);
    BOOST_CHECK((heap_move_construct == heap_copy));

    BOOST_CHECK(((Binary_Heap{} = heap_copy) == heap_copy));

    Binary_Heap heap_move_assign{std::move(heap_move)};
    test(heap_move_assign, 5, false);
    test(heap_move, 0);
    BOOST_CHECK((heap_move_assign == heap_copy));
}
