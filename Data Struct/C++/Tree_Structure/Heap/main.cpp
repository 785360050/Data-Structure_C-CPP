

#include "Binary_Heap.h"

#include <Windows.h>
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


void TestHeap()
{
	Binary_Heap<int> heap(5);
	heap.Heap_Show();
	heap.Heap_Push(1);
	//heap.Heap_Show();
	heap.Heap_Push(2);
	//heap.Heap_Show();
	heap.Heap_Push(3);
	//heap.Heap_Show();
	heap.Heap_Push(4);
	//heap.Heap_Show();
	heap.Heap_Push(5);
	//heap.Heap_Push(6);

	heap.Heap_Show();
	
	std::cout << "TOP = " << heap.Heap_Top() << std::endl;
	heap.Heap_Pop();
	heap.Heap_Show();

}


void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	TestHeap();
}