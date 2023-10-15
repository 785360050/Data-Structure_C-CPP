#include "../API/Liner_Queue.h"

#include <cstring>

///顺序队列
SeqQueue* SeqQueue_Init()
{
	SeqQueue* q = new SeqQueue;
	if (q)
	{
		memset(q->data, 0, sizeof(q->data));
		q->front = 0;
		q->rear = 0;
	}
		
	return q;
}

void SeqQueue_Destory(SeqQueue* SeqQueue)
{
	if (SeqQueue)
		//if (SeqQueue->data)
		//{
		//	free(SeqQueue->data);
		//}			
		//此处应为非malloc申请的空间，而是定义的data[maxsize]，free(SeqQueue->data)后SeqQueue->data是野指针，所以无法free(SeqQueue)
		free(SeqQueue);
}

bool SeqQueue_CheckFull(SeqQueue* SeqQueue)
{
	if ((SeqQueue->rear - SeqQueue->front + 1)%maxsize==SeqQueue->front)
	{
		return true;
	}
	return false;
}

bool SeqQueue_CheckEmpty(SeqQueue* SeqQueue)
{
	if (SeqQueue->front == SeqQueue->rear)
		return true;
	return false;
}

void SeqQueue_Push(SeqQueue* SeqQueue, DataType data)
{
	try
	{
		if (!SeqQueue|| SeqQueue_CheckFull(SeqQueue))
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "SeqQueue is not exist || Queue is Full" << std::endl;
		exit(0);
	}
	SeqQueue->data[SeqQueue->rear] = data;
	SeqQueue->rear= (SeqQueue->rear + 1) % maxsize;

}

DataType SeqQueue_Pop(SeqQueue* SeqQueue)
{
	try
	{
		if (SeqQueue->front==SeqQueue->rear)
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "Queue is empty" << std::endl;
		exit(0);
	}
	DataType t = SeqQueue->data[SeqQueue->front];
	SeqQueue->front = (SeqQueue->front + 1) % maxsize;
	return t;
}



///链式队列
LinkQueue* LinkQueue_Init()
{
	LinkQueue* q = new LinkQueue;
	QueNode* f = new QueNode;
	f->data = 0;
	f->next = NULL;
	q->front = f;
	q->rear = f;
	q->length = 0;
	return q;
}

void LinkQueue_Destroy(LinkQueue* LinkQueue)
{
	delete LinkQueue;
}

void LinkQueue_Push(LinkQueue* LinkQueue, DataType data)
{
	QueNode* n = new QueNode;
	if (LinkQueue->length==0)
	{
		LinkQueue->rear->data = data;
		LinkQueue->length++;
	}
	else
	{
		try
		{
			if (!n)
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "QueNode malloc failed,Push has disrupted"<<std::endl;
			exit(0);
		}
		n->data = data;
		n->next = NULL;
		LinkQueue->rear->next = n;
		LinkQueue->rear = n;
		LinkQueue->length++;
	}
	
}

DataType LinkQueue_Pop(LinkQueue* LinkQueue)
{
	try
	{
		if (LinkQueue->length<=0)
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "Pop faild , LinkQueue is empty" << std::endl;
		exit(0);
	}
	if (LinkQueue->length==1)
	{
		LinkQueue->length--;
		return LinkQueue->front->data;
	}
	else
	{
		DataType t = LinkQueue->front->data;
		QueNode* tn = LinkQueue->front;
		LinkQueue->front = LinkQueue->front->next;
		free(tn);
		LinkQueue->length--;
		return t;
	}
	
}





























