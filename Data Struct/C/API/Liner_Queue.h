#pragma once
#include <iostream>


#define maxsize 10
typedef int DataType;
struct SeqQueue
{
	DataType data[maxsize];
	int front;
	int rear;
};
typedef struct SeqQueue SeqQueue;

//��ʼ��maxsize�ռ��С��˳�����
SeqQueue* SeqQueue_Init();

//�ͷŶ���SeqQueue�ռ�
void SeqQueue_Destory(SeqQueue* SeqQueue);

//����Ԫ��data���SeqQueue
void SeqQueue_Push(SeqQueue* SeqQueue, DataType data);

//Ԫ�س��ӣ���������Ԫ��
DataType SeqQueue_Pop(SeqQueue* SeqQueue);


struct QueNode
{
	DataType data;
	struct QueNode* next;
};
typedef QueNode QueNode;

struct LinkQueue
{
	QueNode* front;
	QueNode* rear;
	int length;
};
typedef struct LinkQueue LinkQueue;

//��ʼ����ʽ���У�������ʽ������
//Ϊ�˱�����ջ�ϴ�����ʽ����ͷ�ڵ��޷���Destroy�ͷ���ͨ����
//������ָ����ͷ�ڵ�
LinkQueue* LinkQueue_Init();

//������ʽ����
void LinkQueue_Destroy(LinkQueue* LinkQueue);

//����Ԫ��data���LinkQueue
void LinkQueue_Push(LinkQueue* LinkQueue, DataType data);

//���ӣ���������Ԫ��
DataType LinkQueue_Pop(LinkQueue* LinkQueue);











