#include "C:/Users/len/Desktop/Data Struct/Data Struct/API/Liner_Stack.h"
#include <iostream>



SeqStack* SeqStack_Init(int stacksize)
{
	SeqStack* s = (SeqStack*)malloc(sizeof(SeqStack));
	if (s)
	{
		memset(s->data, 0, sizeof(s->data));
		s->top = 0;
	}
	return s;
}

void SeqStack_Destroy(SeqStack* stack)
{
	delete stack;
}


void SeqStack_Push(SeqStack* stack, DataType data)
{
	try
	{
		if (stack->top>= StackSize)
		{
			throw "overflow";
		}
	}
	catch (...)
	{
		std::cout << "Stack is Full"<<std::endl;
		exit(0);
	}
	stack->data[stack->top] = data;
	stack->top++;
}

DataType SeqStack_Pop(SeqStack* stack)
{
	try
	{
		if (stack->top<0)
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "Stack is Empty" << std::endl;
		exit(0);
	}
	stack->top--;
	return stack->data[stack->top];
}




















