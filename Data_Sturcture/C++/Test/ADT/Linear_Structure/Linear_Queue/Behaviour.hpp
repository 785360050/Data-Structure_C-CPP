#pragma once

#include <exception>

template <typename QueueType>
void Check_Queue_Empty_State(QueueType &queue)
{
    BOOST_CHECK(queue.Is_Empty());
    BOOST_CHECK_EQUAL(queue.Get_Size(), 0U);
}

template <typename QueueType>
void Check_Queue_Default_Constructed_Behaviour()
{
    QueueType queue;

    Check_Queue_Empty_State(queue);
    BOOST_CHECK_THROW(queue.Get_Front(), std::exception);
    BOOST_CHECK_THROW(queue.Element_Dequeue(), std::exception);
}

template <typename QueueType>
void Check_Queue_Fifo_Behaviour()
{
    QueueType queue;

    queue.Element_Enqueue(10);
    queue.Element_Enqueue(20);
    queue.Element_Enqueue(30);
    BOOST_CHECK_EQUAL(queue.Get_Size(), 3U);
    BOOST_CHECK_EQUAL(queue.Get_Front(), 10);

    queue.Element_Dequeue();
    BOOST_CHECK_EQUAL(queue.Get_Front(), 20);

    queue.Element_Enqueue(40);
    BOOST_CHECK_EQUAL(queue.Get_Front(), 20);

    queue.Element_Dequeue();
    BOOST_CHECK_EQUAL(queue.Get_Front(), 30);
    queue.Element_Dequeue();
    BOOST_CHECK_EQUAL(queue.Get_Front(), 40);
    queue.Element_Dequeue();

    Check_Queue_Empty_State(queue);
}

template <typename QueueType>
void Check_Queue_Clear_Behaviour()
{
    QueueType queue;

    queue.Element_Enqueue(1);
    queue.Element_Enqueue(2);
    queue.Element_Enqueue(3);
    queue.Clear();

    Check_Queue_Empty_State(queue);

    queue.Element_Enqueue(99);
    BOOST_CHECK_EQUAL(queue.Get_Front(), 99);
}

template <typename QueueType>
void Run_Queue_Behaviour_Suite()
{
    Check_Queue_Default_Constructed_Behaviour<QueueType>();
    Check_Queue_Fifo_Behaviour<QueueType>();
    Check_Queue_Clear_Behaviour<QueueType>();
}
