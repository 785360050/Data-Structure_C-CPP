#pragma once


#define 链栈	//[顺序栈/链栈]
#define 顺序栈

typedef int DataType;
#ifdef 顺序栈
//递增满栈(top=0栈空)

//TODO 仅实现顺序栈，且用int的top访问data数组，可用TOP指针
#define StackSize 10
struct SeqStack
{
	DataType data[StackSize];
	int top;
};
typedef struct SeqStack SeqStack;

//申请大小为stacksize的栈空间
SeqStack* SeqStack_Init(int stacksize);
//释放stack所有空间
void SeqStack_Destroy(SeqStack* stack);

//将数据元素data压入栈
void SeqStack_Push(SeqStack* stack, DataType data);
//出栈，并返回数据元素data
DataType SeqStack_Pop(SeqStack* stack);

#endif // 顺序栈

#ifdef 链栈
struct LinkStack
{
	DataType data;
	LinkStack* next;
};
typedef struct LinkStack LinkStack;

//申请大小为stacksize的栈空间
LinkStack* LinkStack_Init();
//释放stack所有空间
void LinkStack_Destroy(LinkStack* stack);

//将数据元素data压入栈
void LinkStack_Push(LinkStack* stack, DataType data);
//出栈，并返回数据元素data
DataType LinkStack_Pop(LinkStack* stack);

#endif // 链栈






