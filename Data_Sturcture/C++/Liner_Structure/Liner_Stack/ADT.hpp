#pragma once

#include <string>
using std::string;

template <typename DataType>
struct Stack_ADT
{///Interface
	virtual ~Stack_ADT() = default;
public:///栈操作
	//清空栈
	virtual void Stack_Clear() = 0;
	//判断是否栈空
	virtual bool Stack_CheckEmpty() = 0;
	//返回栈长度(元素个数)
	virtual int Stack_GetLength() = 0;
	//返回栈顶元素
	virtual DataType Stack_GetTop() = 0;
public:///元素操作
	//元素入栈
	virtual void Element_Push(DataType element) = 0;
	//元素出栈
	virtual void Element_Pop() = 0;

public:
	virtual void Stack_Show(const std::string& string = "") = 0;
};

#if __cplusplus >= 202002L
#include <concepts>

namespace ADT
{
	/// index从1开始，非数组下标从0开始
	template <typename StructureType, typename ElementType>
	concept Liner_Stack = requires(StructureType adt, ElementType element) {
		// 判断是否为空
		adt.Is_Empty();

		// 获取当前元素个数
		adt.Get_Size();
		//获取栈顶元素
		adt.Get_Top();

		// 重置线性表为初始状态，清空所有元素(会析构所有元素)
		adt.Clear();

		// 在index位置插入element
		adt.Element_Push(element);
		// 删除index位置的元素
		adt.Element_Pop();

	};
};
#endif
