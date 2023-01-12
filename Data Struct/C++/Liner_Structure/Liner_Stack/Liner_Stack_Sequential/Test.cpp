#include "Liner_Stack_Sequential.h"

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

void TestSequenceStack_Empty_Ascending()
{
	Sequence_Stack<char> s(5);
	s.Stack_Show("初始化5个单位的栈空间后：");
	for (int i = 65; i < 70; i++)
		s.Element_Push(i);
	s.Stack_Show("压入5个元素后：");
	//s.Stack_Clear();
	std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
	std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
	std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
	while (s.Stack_GetLength() > 0)
		std::cout << s.Element_Pop() << "出栈" << std::endl;

	std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
}

void TestSequenceStack_Full_Ascending()
{
	Sequence_Stack_Full_Ascending<char> s(5);
	s.Stack_Show("初始化5个单位的栈空间后：");
	for (int i = 65; i < 70; i++)
		s.Element_Push(i);
	s.Stack_Show("压入5个元素后：");
	//s.Stack_Clear();
	std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
	std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
	std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
	while (s.Stack_GetLength() > 0)
		std::cout << s.Element_Pop() << "出栈" << std::endl;

	std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;

}

void TestSequenceStack_Empty_Decending()
{
	Sequence_Stack_Empty_Decending<char> s(5);
	s.Stack_Show("初始化5个单位的栈空间后：");
	for (int i = 65; i < 70; i++)
		s.Element_Push(i);
	s.Stack_Show("压入5个元素后：");
	//s.Stack_Clear();
	std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
	std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
	std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
	while (!s.Stack_CheckEmpty())
		std::cout << s.Element_Pop() << "出栈" << std::endl;

	std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;

}

void TestSequenceStack_Full_Decending()
{
	Sequence_Stack_Full_Decending<char> s(5);
	s.Stack_Show("初始化5个单位的栈空间后：");
	for (int i = 65; i < 70; i++)
		s.Element_Push(i);
	s.Stack_Show("压入5个元素后：");
	//s.Stack_Clear();
	std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
	std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
	std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;
	while (!s.Stack_CheckEmpty())
		std::cout << s.Element_Pop() << "出栈" << std::endl;

	std::cout << "栈判空：" << std::boolalpha << s.Stack_CheckEmpty() << std::endl;

}


void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//TestSequenceStack_Empty_Ascending();///空增栈
	//TestSequenceStack_Full_Ascending();///满增栈
	//TestSequenceStack_Empty_Decending();///空减栈
	//TestSequenceStack_Full_Decending();///空减栈
}