#pragma once


#define ��ջ	//[˳��ջ/��ջ]
#define ˳��ջ

typedef int DataType;
#ifdef ˳��ջ
//������ջ(top=0ջ��)

//TODO ��ʵ��˳��ջ������int��top����data���飬����TOPָ��
#define StackSize 10
struct SeqStack
{
	DataType data[StackSize];
	int top;
};
typedef struct SeqStack SeqStack;

//�����СΪstacksize��ջ�ռ�
SeqStack* SeqStack_Init(int stacksize);
//�ͷ�stack���пռ�
void SeqStack_Destroy(SeqStack* stack);

//������Ԫ��dataѹ��ջ
void SeqStack_Push(SeqStack* stack, DataType data);
//��ջ������������Ԫ��data
DataType SeqStack_Pop(SeqStack* stack);

#endif // ˳��ջ

#ifdef ��ջ
struct LinkStack
{
	DataType data;
	LinkStack* next;
};
typedef struct LinkStack LinkStack;

//�����СΪstacksize��ջ�ռ�
LinkStack* LinkStack_Init();
//�ͷ�stack���пռ�
void LinkStack_Destroy(LinkStack* stack);

//������Ԫ��dataѹ��ջ
void LinkStack_Push(LinkStack* stack, DataType data);
//��ջ������������Ԫ��data
DataType LinkStack_Pop(LinkStack* stack);

#endif // ��ջ






