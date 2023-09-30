

#include "Liner_Stack_Linked.hpp"




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
	{
		std::cout << s.Stack_GetTop() << std::endl;
		s.Element_Pop();
	}
}

int main()
{
	TestLinkStack();

	return EXIT_SUCCESS;
}
