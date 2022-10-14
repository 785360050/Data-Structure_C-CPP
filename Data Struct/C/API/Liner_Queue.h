#pragma once

#include "Global Variables.h"
#include <iostream>



typedef int DataType;
struct SeqQueue
{
	DataType data[maxsize];
	int front;
	int rear;
};
typedef struct SeqQueue SeqQueue;

//初始化maxsize空间大小的顺序队列
SeqQueue* SeqQueue_Init();

//释放队列SeqQueue空间
void SeqQueue_Destory(SeqQueue* SeqQueue);

//数据元素data入队SeqQueue
void SeqQueue_Push(SeqQueue* SeqQueue, DataType data);

//元素出队，返回数据元素
DataType SeqQueue_Pop(SeqQueue* SeqQueue);

/// <summary>
/// 链式队列
/// </summary>
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

//初始化链式队列，返回链式队列名
//为了避免在栈上创建链式队列头节点无法用Destroy释放普通变量
//尽量用指针存放头节点
LinkQueue* LinkQueue_Init();

//销毁链式队列
void LinkQueue_Destroy(LinkQueue* LinkQueue);

//数据元素data入队LinkQueue
void LinkQueue_Push(LinkQueue* LinkQueue, DataType data);

//出队，返回数据元素
DataType LinkQueue_Pop(LinkQueue* LinkQueue);

bool SeqQueue_CheckFull(SeqQueue* SeqQueue);
bool SeqQueue_CheckEmpty(SeqQueue* SeqQueue);








