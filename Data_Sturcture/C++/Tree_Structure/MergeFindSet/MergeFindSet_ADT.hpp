#pragma once








template <typename DataType>
class MergeFindSet_ADT
{
protected:
	virtual ~MergeFindSet_ADT() = default;
public:
	//判断查并集set中，元素x,y是否再同一个集合中
	virtual bool Find(DataType x, DataType y) = 0;
	//合并查并集set中元素x,y到同一集合中(x加入y的组)
	virtual void Merge(DataType x, DataType y) = 0;
	//显示整个查并集
	virtual void Show() = 0;
};

#if __cplusplus >= 202002L
#include <concepts>

namespace ADT
{
	/// index从1开始，非数组下标从0开始
	template <typename StructureType, typename ElementType>
	concept MergeFindSet = requires(StructureType adt, ElementType element, std::size_t index) {
		// 判断是否为空
		adt.Is_Empty();

		// 获取当前元素个数
		adt.Get_Size();
		// adt.Get_Capcity();//静态数组才有

		// 重置线性表为初始状态，清空所有元素(会析构所有元素)
		adt.List_Clear();

		// 在index位置插入element
		adt.Element_Insert(index, element);
		// 删除index位置的元素
		adt.Element_Delete(index);
		// 获取index位置的元素
		adt[index];
		// 设置index位置的元素为element
		adt.Element_Update(index, element);
	};
};
#endif