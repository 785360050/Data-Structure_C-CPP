#pragma once

#include "string"
using std::string;


/// @brief 仅实现静态内存分配的队列
/// @tparam DataType 
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
	//判断是否队满
	virtual bool Queue_CheckFull() = 0;
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

#if __cplusplus >= 202002L
#include <concepts>

namespace ADT
{
	/// index从1开始，非数组下标从0开始
	template <typename StructureType, typename ElementType>
	concept Liner_Queue = requires(StructureType adt, ElementType element) {
		// 判断是否为空
		adt.Is_Empty();

		// 获取当前元素个数
		adt.Get_Size();
		// 获取栈顶元素
		adt.Get_Front();

		// 重置线性表为初始状态，清空所有元素(会析构所有元素)
		adt.Clear();

		// 在index位置插入element
		adt.Element_Enqueue(element);
		// 删除index位置的元素
		adt.Element_Dequeue();
	};
};
#endif
