

#include "Link_Stack.hpp"


int main()
{
	Link_Stack<char> s;
	int c = 'Z';
	s.Stack_Show("初始化链栈空间最大为5");
	for (int i = 0; i < 5; i++)
		s.Element_Push(c--);
	s.Stack_Show("插入5个元素后");
	std::cout << "当前栈顶元素为：" << s.Get_Top() << std::endl;
	std::cout << "当前栈长度为：" << s.Get_Size() << std::endl;
	std::cout << "依次出栈" << std::endl;
	while (!s.Is_Empty())
	{
		std::cout << s.Get_Top() << std::endl;
		s.Element_Pop();
	}

	return EXIT_SUCCESS;
}
