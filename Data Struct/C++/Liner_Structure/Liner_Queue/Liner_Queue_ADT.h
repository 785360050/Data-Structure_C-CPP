#pragma once



template<typename DataType>
struct Queue
{///循环队列
public:
	virtual ~Queue() = default;
public:
	//清空队列
	virtual void Queue_Clear() = 0;
	//判断是否队空
	virtual bool Queue_CheckEmpty() = 0;
	//返回队列长度(元素个数)
	virtual int Queue_Length() = 0;
	//返回队头
	virtual DataType Queue_GetHead() = 0;
	//显示整个队列信息
	virtual void Queue_Show(const char* string) = 0;
	//元素入队
	virtual void Element_Enqueue(DataType element) = 0;
	//元素出队
	virtual DataType Element_Dequeue() = 0;
};







