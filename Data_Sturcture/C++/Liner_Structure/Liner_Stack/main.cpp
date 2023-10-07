

#include "Stack.hpp"
#include "Liner_Stack_Sequential/Sequential_Stack.hpp"
#include "Liner_Stack_Linked/Link_Stack.hpp"

template <typename StackType, typename ElementType>
	requires ADT::Liner_Stack<StackType, ElementType>
void TestStack()
{
	StackType *stack = new StackType; /// 链栈

	stack->Stack_Show("初始化5个单位的栈空间后：");
	for (int i = 65; i < 70; i++)
		stack->Element_Push(i);
	stack->Stack_Show("压入5个元素后：");
	// s.Stack_Clear();
	std::cout << "当前栈顶元素为：" << stack->Get_Top() << std::endl;
	std::cout << "当前栈长度为：" << stack->Get_Size() << std::endl;
	std::cout << "栈判空：" << std::boolalpha << stack->Is_Empty() << std::endl;
	while (stack->Get_Size() > 0)
	{
		std::cout << stack->Get_Top() << "出栈" << std::endl;
		stack->Element_Pop();
	}

	std::cout << "栈判空：" << std::boolalpha << stack->Is_Empty() << std::endl;
}

int main()
{
	static_assert(ADT::Liner_Stack<Link_Stack<char>, char>);
	static_assert(ADT::Liner_Stack<Link_Stack<char>, char>);
	static_assert(ADT::Liner_Stack<Link_Stack<char>, char>);
	static_assert(ADT::Liner_Stack<Link_Stack<char>, char>);
	static_assert(ADT::Liner_Stack<Link_Stack<char>, char>);

	TestStack<Link_Stack<char>, char>();

	TestStack<Sequential_Stack<char, 5>, char>();				   /// 空增栈	// Sequential_Stack_Empty_Ascending
	TestStack<Sequential_Stack_Empty_Descending<char, 5>, char>(); /// 空减栈
	TestStack<Sequential_Stack_Full_Ascending<char, 5>, char>();   /// 满增栈
	TestStack<Sequential_Stack_Full_Descending<char, 5>, char>();  /// 满减栈

	return EXIT_SUCCESS;
}
