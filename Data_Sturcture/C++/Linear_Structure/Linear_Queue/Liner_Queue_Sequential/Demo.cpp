#include "Sequential_Queue.hpp"



void Test_SeqQueue_Redundancy()
{
	Sequential_Queue_Redundancy<int,5> q;
	q.Queue_Show("初始化5个队列空间后");
	for (int i = 10; i < 15; i++)
		q.Element_Enqueue(i);
	q.Queue_Show("5个元素入队后");
	const auto& x = q.Get_Front();
	std::cout << "当前队头元素为: " << x << std::endl;
	std::cout << "当前队列长度为: " << q.Get_Size() << std::endl;
	q.Element_Dequeue();
	q.Element_Dequeue();
	q.Queue_Show("出队2个元素后：");
	q.Clear();
	q.Queue_Show("清空队列后");

}

void Test_SeqQueue_Tag()
{
	Sequential_Queue_Tag<int,5> q;
	q.Queue_Show("初始化5个队列空间后");
	for (int i = 10; i < 15; i++)
		q.Element_Enqueue(i);
	
	q.Queue_Show("5个元素入队后");
	std::cout << "是否已满: " <<std::boolalpha<< q.Is_Full() << std::endl;
	std::cout << "当前队头元素为: " << q.Get_Front() << std::endl;
	std::cout << "当前队列长度为: " << q.Get_Size() << std::endl;
	q.Element_Dequeue();
	q.Element_Dequeue();
	q.Queue_Show("出队2个元素后：");
	q.Clear();
	q.Queue_Show("清空队列后");

}

int main()
{
	Test_SeqQueue_Redundancy();
	Test_SeqQueue_Tag();

	return EXIT_SUCCESS;
}
