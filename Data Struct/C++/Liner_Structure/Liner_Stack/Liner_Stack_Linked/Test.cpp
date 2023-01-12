

#include "Liner_Stack_Linked.h"

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

void TestLinkStack()
{
	Link_Stack<char> s(5);
	int c = 'Z';
	s.Stack_Show("初始化链栈空间最大为5");
	for (int i = 0; i < 5; i++)
		s.Element_Push(c--);
	s.Stack_Show("插入5个元素后");
	std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
	std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
	std::cout << "依次出栈" << std::endl;
	while (!s.Stack_CheckEmpty())
		std::cout << s.Element_Pop() << std::endl;
}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	TestLinkStack();
}
