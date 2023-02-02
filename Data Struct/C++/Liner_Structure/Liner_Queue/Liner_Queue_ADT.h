#pragma once

#include "string"
using std::string;

template<typename DataType>
struct Queue_ADT
{///Interface
public:
	virtual ~Queue_ADT() = default;
public:
	//清空队列
	virtual void Queue_Clear() = 0;
	//判断是否队空
	virtual bool Queue_CheckEmpty() = 0;
	//返回队列长度(元素个数)
	virtual int Queue_Length() = 0;
	//返回队头
	virtual DataType Queue_GetFront() = 0;
	//返回队尾
	virtual DataType Queue_GetRear() = 0;
	//显示整个队列信息
	virtual void Queue_Show(const std::string& string="") = 0;
	//元素入队
	virtual void Element_Enqueue(DataType element) = 0;
	//元素出队
	virtual void Element_Dequeue() = 0;
};







