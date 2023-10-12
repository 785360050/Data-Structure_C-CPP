

#define BOOST_TEST_MODULE Binary_Heap
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <limits>
#include <iostream>
#include <list>

// #include "../../../../Linear_Structure/Linear_Stack/Linear_Stack_Linked/Link_Stack.hpp"
#include "Binary_Heap.hpp"

// #include "../../../../Test/Unit_Test/Test_Element.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework -std=c++20



void test(const Binary_Heap<int, 5> &heap, size_t size = 0, bool empty = true)
{
    BOOST_CHECK(heap.Get_Size() == size);
    BOOST_CHECK(heap.Is_Empty() == empty);
};

#include <vector>
/// @brief 检查是否为按对应比较方式的堆，O(n)的空间复杂度
template <typename Binary_Heap, typename ElementType, typename Compare>
void Check(Binary_Heap heap)
{
    std::vector<ElementType> v;
    while (!heap.Is_Empty())
    {
        v.push_back(heap.Get_Top());
        heap.Pop();
    }

    // 由于is_heap使用Compare{}(孩子，父亲)，而Binary_Heap使用Compare{}(父亲，孩子)，因此需要反转
    // 晚点再自己写一个吧，感觉不放心
    BOOST_CHECK(!std::is_heap(v.begin(), v.end(), Compare{}));
}

BOOST_AUTO_TEST_CASE(Con_Destruct)
{
    { // Sequential_Queue_Redundancy

        Binary_Heap<int,5> heap;
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
    Binary_Heap<int, 5> heap{5, 4, 3, 2, 1};
    test(heap,5,false);
    Check<decltype(heap), int, std::less<>>(heap);
}

// BOOST_AUTO_TEST_CASE(Template_Parameter)
// {
//     Link_Stack<char> heap;
//     Link_Stack<const char *> stack1;
//     Link_Stack<int *> stack2;
//     Link_Stack<Element<int>> stack3;
//     Link_Stack<Element<char *> *> stack4;
//     Link_Stack<size_t> stack5;

//     stack1.Element_Push("Hello");
//     stack1.Element_Push("World");
//     stack1.Clear();

// }




BOOST_AUTO_TEST_CASE(Operations)
{
    // Binary_Heap<int> heap(5,Property::large);
    
    Binary_Heap<int,5> heap_min;//小根堆
    BOOST_CHECK(heap_min.Get_Size() == 0);
    BOOST_CHECK(heap_min.Is_Empty());

    for (int i = 0; i < 5; i++)
    {
        heap_min.Push(i);
        BOOST_CHECK(heap_min.Get_Top() == 0);
    }
    Check<decltype(heap_min), int,std::less<>>(heap_min);
    Binary_Heap<int, 5, std::greater<>> heap_max; // 大根堆
    for (int i = 0; i < 5; i++)
    {
        heap_max.Push(i);
        BOOST_CHECK(heap_max.Get_Top() == i);
    }
    Check<decltype(heap_max), int, std::greater<>>(heap_max);

    // while(heap.length>0)
    // {
    //     heap.Heap_Pop()
    // }

}

// BOOST_AUTO_TEST_CASE(Operations_With_Element)
// {
//     using ElementType = Element<size_t>;

//     Link_Stack<ElementType> heap;

//     for (size_t i = 1; i <= 5; i++)
//         heap.Element_Push({i,i});

//     BOOST_CHECK(heap.Get_Size() == 5);

//     for (size_t i = 5;i>=1; i--)
//     {
//         BOOST_CHECK(heap.Get_Top() == ElementType(i, i));
//         heap.Element_Pop();
//     }
//     BOOST_CHECK(heap.Get_Size() == 0);
//     BOOST_CHECK(heap.Is_Empty());

//     // static_assert(std::is_pointer<int>::value == std::false_type());
//     heap.Clear();
//     BOOST_CHECK(heap.Get_Size() == 0);
// }

// template <typename StackType>
// void Prepare_Element(StackType &heap, std::initializer_list<int> list)
// {
//     // BOOST_REQUIRE_GE(5, list.size());
//     for (auto &e : list)
//         heap.Element_Push(e);
// };
// template <typename StackType>
// void Check_Element(StackType heap, std::initializer_list<int> list)
// {
//     // BOOST_REQUIRE_EQUAL(heap.Get_Size(), list.size());

//     for (auto &e : list)
//     {
//         BOOST_CHECK(heap.Get_Top() == e);
//         heap.Element_Pop();
//     }
// };
// BOOST_AUTO_TEST_CASE(Copy_Control)
// {

//     {
//         Link_Stack<int> heap;
//         test(heap, 0);
//         std::initializer_list<int> list{1, 2, 3, 4, 5};
//         std::initializer_list<int> list_reverse {5, 4, 3, 2, 1};
//         Prepare_Element<Link_Stack<int>>(heap, list);
//         Check_Element<Link_Stack<int>>(heap, list_reverse);

//         auto stack_copy_construct(heap);
//         test(stack_copy_construct, 5, false);
//         Check_Element<Link_Stack<int>>(stack_copy_construct, list_reverse);
//         auto stack_copy_assign = heap;
//         test(stack_copy_assign, 5, false);
//         Check_Element<Link_Stack<int>>(stack_copy_assign, list_reverse);

//         auto stack_move_construct(std::move(heap));
//         test(stack_move_construct, 5, false);
//         test(heap, 0, 6);
//         Check_Element<Link_Stack<int>>(stack_move_construct, list_reverse);
//         auto stack_move_assign = std::move(stack_move_construct);
//         test(stack_move_assign, 5, false);
//         test(stack_move_construct, 0, 6);
//         Check_Element<Link_Stack<int>>(stack_move_assign, list_reverse);
//     }
// }
