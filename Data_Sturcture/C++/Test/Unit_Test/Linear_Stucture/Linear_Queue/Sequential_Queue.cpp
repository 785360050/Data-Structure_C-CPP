

#define BOOST_TEST_MODULE Sequential_Queue
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <limits>
#include <iostream>

#include "../../../../Linear_Structure/Linear_Queue/Liner_Queue_Sequential/Sequential_Queue.hpp"

#include "../../../../Test/Unit_Test/Test_Element.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework -std=c++20

void test(const Sequential_Queue_Redundancy<int, 5> &queue, size_t size = 0, size_t capcity = 0, bool empty = true, bool full = false)
{
    BOOST_CHECK(queue.Get_Size() == size);
    BOOST_CHECK(queue.Get_Capcity() == capcity);
    BOOST_CHECK(queue.Is_Empty() == empty);
    BOOST_CHECK(queue.Is_Full() == full);
};
void test(const Sequential_Queue_Tag<int, 5> &queue, size_t size = 0, size_t capcity = 0, bool empty = true, bool full = false)
{
    BOOST_CHECK(queue.Get_Size() == size);
    BOOST_CHECK(queue.Get_Capcity() == capcity);
    BOOST_CHECK(queue.Is_Empty() == empty);
    BOOST_CHECK(queue.Is_Full() == full);
};

BOOST_AUTO_TEST_CASE(Con_Destruct_Copy)
{
    { // Sequential_Queue_Redundancy

        Sequential_Queue_Redundancy<int, 5> queue;
        test(queue, 0, 6);

        auto queue_copy_construct(queue);
        test(queue_copy_construct, 0, 6);
        auto queue_copy_assign = queue;
        test(queue_copy_assign, 0, 6);

        auto queue_move_construct(Sequential_Queue_Redundancy<int, 5>{});
        test(queue_move_construct, 0, 6);
        auto queue_move_assign = std::move(queue);
        test(queue_move_assign, 0, 6);
    }

    { // Sequential_Queue_Tag

        Sequential_Queue_Tag<int, 5> queue;
        test(queue, 0, 5);

        auto queue_copy_construct(queue);
        test(queue_copy_construct, 0, 5);
        auto queue_copy_assign = queue;
        test(queue_copy_assign, 0, 5);

        auto queue_move_construct(Sequential_Queue_Tag<int, 5>{});
        test(queue_move_construct, 0, 5);
        auto queue_move_assign = std::move(queue);
        test(queue_move_assign, 0, 5);
    }
}

BOOST_AUTO_TEST_CASE(Template_Parameter)
{
    Sequential_Queue_Redundancy<char, 5> queue;
    Sequential_Queue_Redundancy<const char *, 5> queue1;
    Sequential_Queue_Redundancy<int *, 5> queue2;
    Sequential_Queue_Redundancy<Element<int>, 5> queue3;
    Sequential_Queue_Redundancy<Element<char *> *, 5> queue4;
    Sequential_Queue_Redundancy<size_t, 5> queue5;

    queue1.Element_Enqueue("Hello");
    queue1.Element_Enqueue("World");
    queue1.Clear();

    // //暂时先限制元素类型为非指针类型
    //     Sequential_List_Static<Element<int> *, 5> clear_pointer;
    //     for (int i = 1; i <= 5; i++)
    //         clear_pointer.Element_Insert(i, new Element(i,10+i));

    //     clear_pointer.List_Clear();
}

BOOST_AUTO_TEST_CASE(Operations)
{
    Sequential_Queue_Redundancy<int, 5> queue_R;

    for (int i = 1; i <= 5; i++)
        queue_R.Element_Enqueue(i);

    BOOST_CHECK(queue_R.Is_Full());
    BOOST_CHECK_THROW(queue_R.Element_Enqueue(0), std::runtime_error);
    BOOST_CHECK(queue_R.Get_Size() == 5);
    BOOST_CHECK(queue_R.Get_Capcity() == 6);

    for (int i = 1; i <= 5; i++)
    {
        BOOST_CHECK(queue_R.Get_Front() == i);
        queue_R.Element_Dequeue();
    }
    BOOST_CHECK_THROW(queue_R.Element_Dequeue(), std::runtime_error);
    BOOST_CHECK(queue_R.Get_Size() == 0);
    BOOST_CHECK(queue_R.Is_Empty());

    // static_assert(std::is_pointer<int>::value == std::false_type());
    queue_R.Clear();
    BOOST_CHECK(queue_R.Get_Size() == 0);
    BOOST_CHECK(queue_R.Get_Capcity() == 6);

    // Tag
    Sequential_Queue_Tag<int, 5> queue_T;

    for (int i = 1; i <= 5; i++)
        queue_T.Element_Enqueue(i);

    BOOST_CHECK(queue_T.Is_Full());
    BOOST_CHECK_THROW(queue_T.Element_Enqueue(0), std::runtime_error);
    BOOST_CHECK(queue_T.Get_Size() == 5);
    BOOST_CHECK(queue_T.Get_Capcity() == 5);

    for (int i = 1; i <= 5; i++)
    {
        BOOST_CHECK(queue_T.Get_Front() == i);
        queue_T.Element_Dequeue();
    }
    BOOST_CHECK_THROW(queue_T.Element_Dequeue(), std::runtime_error);
    BOOST_CHECK(queue_T.Get_Size() == 0);
    BOOST_CHECK(queue_T.Is_Empty());

    // static_assert(std::is_pointer<int>::value == std::false_type());
    queue_T.Clear();
    BOOST_CHECK(queue_T.Get_Size() == 0);
    BOOST_CHECK(queue_T.Get_Capcity() == 5);
}

BOOST_AUTO_TEST_CASE(Operations_With_Element)
{
    using ElementType = Element<size_t>;
    { // Sequential_Queue_Redundancy

        Sequential_Queue_Redundancy<ElementType, 5> queue_R;

        for (size_t i = 1; i <= 5; i++)
            queue_R.Element_Enqueue({i, i});

        BOOST_CHECK(queue_R.Is_Full());
        BOOST_CHECK_THROW(queue_R.Element_Enqueue({0, 0}), std::runtime_error);
        BOOST_CHECK(queue_R.Get_Size() == 5);
        BOOST_CHECK(queue_R.Get_Capcity() == 6);

        for (size_t i = 1; i <= 5; i++)
        {
            BOOST_CHECK(queue_R.Get_Front() == ElementType(i, i));
            queue_R.Element_Dequeue();
        }
        BOOST_CHECK_THROW(queue_R.Element_Dequeue(), std::runtime_error);
        BOOST_CHECK(queue_R.Get_Size() == 0);
        BOOST_CHECK(queue_R.Is_Empty());

        // static_assert(std::is_pointer<int>::value == std::false_type());
        queue_R.Clear();
        BOOST_CHECK(queue_R.Get_Size() == 0);
        BOOST_CHECK(queue_R.Get_Capcity() == 6);
    }

    { // Tag

        Sequential_Queue_Tag<ElementType, 5> queue_T;

        for (size_t i = 1; i <= 5; i++)
            queue_T.Element_Enqueue({i, i});

        BOOST_CHECK(queue_T.Is_Full());
        BOOST_CHECK_THROW(queue_T.Element_Enqueue({0, 0}), std::runtime_error);
        BOOST_CHECK(queue_T.Get_Size() == 5);
        BOOST_CHECK(queue_T.Get_Capcity() == 5);

        for (size_t i = 1; i <= 5; i++)
        {
            BOOST_CHECK(queue_T.Get_Front() == ElementType(i, i));
            queue_T.Element_Dequeue();
        }
        BOOST_CHECK_THROW(queue_T.Element_Dequeue(), std::runtime_error);
        BOOST_CHECK(queue_T.Get_Size() == 0);
        BOOST_CHECK(queue_T.Is_Empty());

        // static_assert(std::is_pointer<int>::value == std::false_type());
        queue_T.Clear();
        BOOST_CHECK(queue_T.Get_Size() == 0);
        BOOST_CHECK(queue_T.Get_Capcity() == 5);
    }
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

    { // Sequential_Queue_Redundancy
        Sequential_Queue_Redundancy<int, 5> queue;
        test(queue, 0, 6);
        std::initializer_list<int> list{1, 2, 3, 4, 5}; // 元素数量不要超过队列分配的空间，没有逻辑检查
        Prepare_Element<Sequential_Queue_Redundancy<int, 5>>(queue, list);
        Check_Element<Sequential_Queue_Redundancy<int, 5>>(queue, list);

        auto queue_copy_construct(queue);
        test(queue_copy_construct, 5, 6, false, true);
        Check_Element<Sequential_Queue_Redundancy<int, 5>>(queue_copy_construct, list);
        auto queue_copy_assign = queue;
        test(queue_copy_assign, 5, 6, false, true);
        Check_Element<Sequential_Queue_Redundancy<int, 5>>(queue_copy_assign, list);

        auto queue_move_construct(std::move(queue));
        test(queue_move_construct, 5, 6, false, true);
        test(queue, 0, 6);
        Check_Element<Sequential_Queue_Redundancy<int, 5>>(queue_move_construct, list);
        auto queue_move_assign = std::move(queue_move_construct);
        test(queue_move_assign, 5, 6, false, true);
        test(queue_move_construct, 0, 6);
        Check_Element<Sequential_Queue_Redundancy<int, 5>>(queue_move_assign, list);
    }
    { // Sequential_Queue_Tag
        Sequential_Queue_Tag<int, 5> queue;
        test(queue, 0, 5);
        std::initializer_list<int> list{1, 2, 3, 4, 5}; // 元素数量不要超过队列分配的空间，没有逻辑检查
        Prepare_Element<Sequential_Queue_Tag<int, 5>>(queue, list);
        Check_Element<Sequential_Queue_Tag<int, 5>>(queue, list);

        auto queue_copy_construct(queue);
        test(queue_copy_construct, 5, 5, false, true);
        Check_Element<Sequential_Queue_Tag<int, 5>>(queue_copy_construct, list);
        auto queue_copy_assign = queue;
        test(queue_copy_assign, 5, 5, false, true);
        Check_Element<Sequential_Queue_Tag<int, 5>>(queue_copy_assign, list);

        auto queue_move_construct(std::move(queue));
        test(queue_move_construct, 5, 5, false, true);
        test(queue, 0, 5);
        Check_Element<Sequential_Queue_Tag<int, 5>>(queue_move_construct, list);
        auto queue_move_assign = std::move(queue_move_construct);
        test(queue_move_assign, 5, 5, false, true);
        test(queue_move_construct, 0, 5);
        Check_Element<Sequential_Queue_Tag<int, 5>>(queue_move_assign, list);
    }
}