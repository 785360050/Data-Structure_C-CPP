#pragma once

#include <string>
using std::string;


//线性表
template <typename ElementType,typename DataType>
class Liner_List_ADT
{///Interface
public:
	virtual ~Liner_List_ADT() = default;
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
	template <typename StructureType, typename ElementType>
	concept Liner_List = requires(StructureType adt, ElementType element, std::size_t index) {
		adt.Is_Empty();
		adt.Get_Size();
		adt.Get_Capcity();
		adt.List_Clear();

		adt.Element_Insert(index, element);
		adt.Element_Delete(index);
		adt[index];
		adt.Element_Update(index, element);
	};
};
#endif
