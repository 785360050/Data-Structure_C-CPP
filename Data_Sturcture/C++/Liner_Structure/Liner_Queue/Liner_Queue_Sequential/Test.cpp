#include "Liner_Queue_Sequential.hpp"



void Test_SeqQueue_Redundancy()
{
	Sequence_Queue<int> q(5);
	q.Queue_Show("初始化5个队列空间后");
	for (int i = 10; i < 15; i++)
		q.Element_Enqueue(i);
	q.Queue_Show("5个元素入队后");
	std::cout << "当前队头元素为: " << q.Queue_GetFront() << std::endl;
	std::cout << "当前队尾元素为: " << q.Queue_GetRear() << std::endl;
	std::cout << "当前队列长度为: " << q.Queue_Length() << std::endl;
	q.Element_Dequeue();
	q.Element_Dequeue();
	q.Queue_Show("出队2个元素后：");
	q.Queue_Clear();
	q.Queue_Show("清空队列后");

}

void Test_SeqQueue_Tag()
{
	Sequence_Queue_Tag<int> q(5);
	q.Queue_Show("初始化5个队列空间后");
	for (int i = 10; i < 15; i++)
		q.Element_Enqueue(i);
	
	q.Queue_Show("5个元素入队后");
	std::cout << "当前队头元素为: " << q.Queue_GetFront() << std::endl;
	std::cout << "当前队列长度为: " << q.Queue_Length() << std::endl;
	q.Element_Dequeue();
	q.Element_Dequeue();
	q.Queue_Show("出队2个元素后：");
	q.Queue_Clear();
	q.Queue_Show("清空队列后");

}

int main()
{
	Test_SeqQueue_Redundancy();
	//Test_SeqQueue_Tag();

	return EXIT_SUCCESS;
}
