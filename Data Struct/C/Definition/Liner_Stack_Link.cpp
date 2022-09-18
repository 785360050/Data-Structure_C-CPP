#include "../API/Liner_Stack.h"
#include <iostream>

LinkStack* LinkStack_Init()
{
	LinkStack* p = (LinkStack*)malloc(sizeof(LinkStack));
	p->next = (LinkStack*)malloc(sizeof(p->next));
	p->next = NULL;
	return p;
}

void LinkStack_Destroy(LinkStack* stack)
{
	try
	{
		if (!stack)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Inexsistent Stack" << std::endl;
		exit(0);
	}
	while (stack->next)
	{
		LinkStack_Pop(stack);
	}
	free(stack);

}

void LinkStack_Push(LinkStack* stack, DataType data)
{
	LinkStack* p=(LinkStack* )malloc(sizeof(LinkStack));
	p->data = data;
	p->next = stack->next;
	stack->next = p;
}

DataType LinkStack_Pop(LinkStack* stack)
{
	try
	{
		if (!stack->next)
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "Stack is empty" << std::endl;
		exit(0);
	}
	LinkStack* t = stack->next;
	DataType x = stack->next->data;
	stack->next = t->next;
	free(t);
	return x;
}




















