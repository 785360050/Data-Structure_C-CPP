

#define BOOST_TEST_MODULE Sequential_Queue
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <limits>
#include <iostream>

#include "../../../../Liner_Structure/Liner_Queue/Liner_Queue_Linked/Link_Queue.hpp"

#include "../../../../Test/Unit_Test/Test_Element.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework -std=c++20

void test(const Link_Queue<int> &queue, size_t size = 0,  bool empty = true)
{
    BOOST_CHECK(queue.Get_Size() == size);
    BOOST_CHECK(queue.Is_Empty() == empty);
};


BOOST_AUTO_TEST_CASE(Con_Destruct_Copy)
{
    { // Sequential_Queue_Redundancy


        Link_Queue<int> queue;
        test(queue, 0);

        auto queue_copy_construct(queue);
        test(queue_copy_construct, 0);
        auto queue_copy_assign = queue;
        test(queue_copy_assign, 0);

        auto queue_move_construct(Link_Queue<int>{});
        test(queue_move_construct, 0);
        auto queue_move_assign = std::move(queue);
        test(queue_move_assign, 0);
    }

}

BOOST_AUTO_TEST_CASE(Template_Parameter)
{
    Link_Queue<char> queue;
    Link_Queue<const char *> queue1;
    Link_Queue<int *> queue2;
    Link_Queue<Element<int>> queue3;
    Link_Queue<Element<char *> *> queue4;
    Link_Queue<size_t> queue5;

    queue1.Element_Enqueue("Hello");
    queue1.Element_Enqueue("World");
    queue1.Clear();

    // //暂时先限制元素类型为非指针类型
    //     Sequential_List_Static<Element<int> *> clear_pointer;
    //     for (int i = 1; i <= 5; i++)
    //         clear_pointer.Element_Insert(i, new Element(i,10+i));

    //     clear_pointer.List_Clear();
}

BOOST_AUTO_TEST_CASE(Operations)
{
    using ElementType = int;

    Link_Queue<int> queue_R;

    for (size_t i = 1; i <= 5; i++)
        queue_R.Element_Enqueue(i);

    BOOST_CHECK(queue_R.Get_Size() == 5);

    for (size_t i = 1; i <= 5; i++)
    {
        BOOST_CHECK(queue_R.Get_Front() == i);
        queue_R.Element_Dequeue();
    }
    BOOST_CHECK(queue_R.Get_Size() == 0);
    BOOST_CHECK(queue_R.Is_Empty());

    // static_assert(std::is_pointer<int>::value == std::false_type());
    queue_R.Clear();
    BOOST_CHECK(queue_R.Get_Size() == 0);

}

BOOST_AUTO_TEST_CASE(Operations_With_Element)
{
    using ElementType = Element<size_t>;

    Link_Queue<ElementType> queue_R;

    for (size_t i = 1; i <= 5; i++)
        queue_R.Element_Enqueue({i,i});

    BOOST_CHECK(queue_R.Get_Size() == 5);

    for (size_t i = 1; i <= 5; i++)
    {
        BOOST_CHECK(queue_R.Get_Front() == ElementType(i, i));
        queue_R.Element_Dequeue();
    }
    BOOST_CHECK(queue_R.Get_Size() == 0);
    BOOST_CHECK(queue_R.Is_Empty());

    // static_assert(std::is_pointer<int>::value == std::false_type());
    queue_R.Clear();
    BOOST_CHECK(queue_R.Get_Size() == 0);
}

template <typename QueueType>
void Prepare_Element(QueueType &queue, std::initializer_list<int> list)
{
    // BOOST_REQUIRE_GE(5, list.size());
    for (auto &e : list)
        queue.Element_Enqueue(e);
};
template <typename QueueType>
void Check_Element(QueueType queue, std::initializer_list<int> list)
{
    // BOOST_REQUIRE_EQUAL(queue.Get_Size(), list.size());
    for (auto &e : list)
    {
        BOOST_CHECK(queue.Get_Front() == e);
        queue.Element_Dequeue();
    }
};
BOOST_AUTO_TEST_CASE(Copy_Control)
{

    {
        Link_Queue<int> queue;
        test(queue, 0);
        std::initializer_list<int> list{1, 2, 3, 4, 5}; 
        Prepare_Element<Link_Queue<int>>(queue, list);
        Check_Element<Link_Queue<int>>(queue, list);

        auto queue_copy_construct(queue);
        test(queue_copy_construct, 5, false);
        Check_Element<Link_Queue<int>>(queue_copy_construct, list);
        auto queue_copy_assign = queue;
        test(queue_copy_assign, 5, false);
        Check_Element<Link_Queue<int>>(queue_copy_assign, list);

        auto queue_move_construct(std::move(queue));
        test(queue_move_construct, 5, false);
        test(queue, 0, 6);
        Check_Element<Link_Queue<int>>(queue_move_construct, list);
        auto queue_move_assign = std::move(queue_move_construct);
        test(queue_move_assign, 5, false);
        test(queue_move_construct, 0, 6);
        Check_Element<Link_Queue<int>>(queue_move_assign, list);
    }
}
