#pragma once

#include <string>
using std::string;

// 废弃的接口类
//线性表
template <typename ElementType,typename DataType>
class Linear_List_ADT
{///Interface
public:
	virtual ~Linear_List_ADT() = default;
protected:
	size_t Index(size_t pos) const;
public:///表操作
	//清空所有元素
	virtual void List_Clear() = 0;
	//判断是否表空
	virtual bool List_CheckEmpty() const = 0;
	//返回表长(元素个数)
	virtual size_t List_GetLength() const = 0;
	//返回第pos个元素的元素值
	virtual DataType List_GetData(size_t pos) = 0;
public:///元素操作
	virtual ElementType* Element_Locate(size_t pos) = 0;
	//插入元素
	virtual void Element_Insert(size_t pos, DataType elem) = 0;
	//删除元素
	virtual DataType Element_Delete(size_t pos) = 0;
	//更新元素
	virtual void Element_Update(size_t pos, DataType elem) = 0;
public:
	//显示线性表所有信息
	virtual void List_Show(const string& string="") = 0;
};

#if __cplusplus >= 202002L
#include <concepts>

namespace ADT
{
	/// index从1开始，非数组下标从0开始
	template <typename StructureType, typename ElementType>
	concept Linear_List = requires(StructureType adt, ElementType &&element, std::size_t index) {

		// 判断是否为空
		adt.Is_Empty();

		// 获取当前元素个数
		adt.Get_Size();
		// adt.Get_Capcity();//静态数组才有
		
		// 重置线性表为初始状态，清空所有元素(会析构所有元素)
		adt.List_Clear();

		// 在index位置插入element
		adt.Element_Insert(index, std::forward<ElementType>(element));
		// 删除index位置的元素
		adt.Element_Delete(index);
		// 获取index位置的元素
		adt[index];
		// 设置index位置的元素为element
		adt.Element_Update(index, std::forward<ElementType>(element));
	};
};
#endif
