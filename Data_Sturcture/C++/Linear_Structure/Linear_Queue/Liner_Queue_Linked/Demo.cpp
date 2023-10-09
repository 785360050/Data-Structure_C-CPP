#include "Link_Queue.hpp"

#ifdef _Win32 // ARM32/64, x86/x64
// 详见 https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
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
#endif

void Test_LinkQueue()
{
	Link_Queue<int, List_Node_SingleWay<int>> q;
	q.Queue_Show("初始化队列后");
	for (int i = 10; i < 15; i++)
		q.Element_Enqueue(i);
	q.Queue_Show("5个元素入队后");
	std::cout << "当前队头元素为: " << q.Get_Front()<< std::endl;
	std::cout << "当前队列长度为: " << q.Get_Size() << std::endl;
	q.Element_Dequeue();
	q.Element_Dequeue();
	q.Queue_Show("出队2个元素后：");
	q.Clear();
	q.Queue_Show("清空队列后");

}



int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	Test_LinkQueue();

	return EXIT_SUCCESS;
}
