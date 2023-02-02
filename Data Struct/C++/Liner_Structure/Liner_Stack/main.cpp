





#include "Liner_Stack_ADT.h"
#include "Liner_Stack_Linked/Liner_Stack_Linked.h"
#include "Liner_Stack_Sequential/Liner_Stack_Sequential.h"

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

void TestStack()
{
	Stack<char>* stack=new Sequence_Stack<char>(5);						///空增栈
	//Stack<char>* stack=new Sequence_Stack_Empty_Decending<char>(5);	///空减栈
	//Stack<char>* stack=new Sequence_Stack_Full_Ascending<char>(5);	///满增栈
	//Stack<char>* stack=new Sequence_Stack_Full_Decending<char>(5);	///满减栈
	//Stack<char>* stack=new Link_Stack<char>(5);						///链栈

	stack->Stack_Show("初始化5个单位的栈空间后：");
	for (int i = 65; i < 70; i++)
		stack->Element_Push(i);
	stack->Stack_Show("压入5个元素后：");
	//s.Stack_Clear();
	std::cout << "当前栈顶元素为：" << stack->Stack_GetTop() << std::endl;
	std::cout << "当前栈长度为：" << stack->Stack_GetLength() << std::endl;
	std::cout << "栈判空：" << std::boolalpha << stack->Stack_CheckEmpty() << std::endl;
	while (stack->Stack_GetLength() > 0)
	{
		std::cout << stack->Stack_GetTop() << "出栈" << std::endl;
		stack->Element_Pop();
	}

	std::cout << "栈判空：" << std::boolalpha << stack->Stack_CheckEmpty() << std::endl;
}


void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//TestSequenceStack_Empty_Ascending();///空增栈
	//TestSequenceStack_Full_Ascending();///满增栈
	//TestSequenceStack_Empty_Decending();///空减栈
	//TestSequenceStack_Full_Decending();///空减栈
	TestStack();
}