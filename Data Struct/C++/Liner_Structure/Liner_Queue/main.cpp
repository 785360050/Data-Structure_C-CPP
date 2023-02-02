



#include "Liner_Queue_ADT.h"
#include "Liner_Queue_Linked/Liner_Queue_Linked.h"
#include "Liner_Queue_Sequential/Liner_Queue_Sequential.h"


#include <Windows.h>
///修改cmd编码方式
static bool  SetEncode(int EncodeId = 936)
{
	/// <summary>
	/// EncodeId 是代码页，设置它等于设置我们指定的编码格式。
	///	默认936为unicode编码
	/// SetConsoleCP() 设置控制台输入时使用的编码。
	///	SetConsoleOutputCP() 设置控制台输出时使用的编码。
	/// </summary>
	/// <param name="EncodeId"></param>
	/// <returns></returns>
	return SetConsoleCP(EncodeId) && SetConsoleOutputCP(EncodeId);
}

void Test_Queue()
{
	//Queue<int>* q = new Sequence_Queue<int>(5);
	//Queue<int>* q = new Sequence_Queue_Tag<int>(5);
	Queue<int>* q = new Link_Queue<List_Node_SingleWay<int>, int>(5);
	q->Queue_Show("初始化5个队列空间后");
	for (int i = 10; i < 15; i++)
		q->Element_Enqueue(i);
	q->Queue_Show("5个元素入队后");
	std::cout << "当前队头元素为: " << q->Queue_GetFront() << std::endl;
	std::cout << "当前队列长度为: " << q->Queue_Length() << std::endl;
	q->Element_Dequeue();
	q->Element_Dequeue();
	q->Queue_Show("出队2个元素后：");
	q->Queue_Clear();
	q->Queue_Show("清空队列后");

}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	Test_Queue();
}


