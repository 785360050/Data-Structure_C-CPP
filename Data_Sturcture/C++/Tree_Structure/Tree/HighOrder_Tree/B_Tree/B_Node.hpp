#pragma once

#if __cplusplus >= 202002L
#include <concepts>

namespace ADT
{
	/// index从1开始，非数组下标从0开始
	template <typename StructureType, typename KeyType, typename ElementType>
	concept B_Node = requires(StructureType adt, KeyType &&key, ElementType &&element) {
		// 判断是否为空
		adt.Is_Empty();

		// 获取当前元素个数
		adt.Get_Size();
		// adt.Get_Capcity();//静态数组才有

		// 重置线性表为初始状态，清空所有元素(会析构所有元素)
		adt.Clear();

		// 返回
		adt.Locate_Key(key);
		// 在index位置插入element
		adt.Element_Insert(key, element);
		// 删除index位置的元素
		adt.Element_Delete(key);
		// 获取key对应的元素
		adt[key]; // ElementType&
		// // 设置index位置的元素为element
		// adt.Element_Update(key,element);
	};

	/// index从1开始，非数组下标从0开始
	template <typename StructureType, typename KeyType>
	concept Index_Node = requires(StructureType adt, KeyType &&key {
		// 判断是否为空
		adt.Is_Empty();

		// 获取当前元素个数
		adt.Get_Size();
		// adt.Get_Capcity();//静态数组才有

		// 重置线性表为初始状态，清空所有元素(会析构所有元素)
		adt.Clear();

		// 返回
		adt.Locate_Key(key);
		adt.child[key]
		// 在index位置插入element
		adt.Element_Insert(key, element);
		// 删除index位置的元素
		adt.Element_Delete(key);
		// 获取key对应的元素
		adt[key]; // ElementType&
				  // // 设置index位置的元素为element
				  // adt.Element_Update(key,element);
	};
};
#endif

template <typename KeyType, typename ElementType, size_t order>
struct B_Node
{
	KeyType storage_key[order]{}; /// 存放关键字 ///order-1个元素用于存储，最后一个元素空间用于预存,如插入时预存分割元素
	size_t size{};		  /// 节点当前key个数
	B_Node *parent{nullptr};	  /// 父节点
	B_Node(int order)
	{
		static_assert(order > 2, "order must be greater than 2");
	}
};

/// @brief
/// @tparam DataType
/// @tparam order 节点阶数
template <typename KeyType, typename ElementType, size_t order>
struct B_Node_Index:public B_Node<KeyType, ElementType, order>
{
	B_Node *storage_child[order]{}; /// 存放指针索引
};

template <typename KeyType, typename ElementType, size_t order>
struct B_Node_Leaf
{
	ElementType storage_element[order]{}; /// 存放元素
};

template <typename KeyType, typename ElementType, size_t order>
struct B_Node:public B_Node_Index<KeyType, ElementType, order>, public B_Node_Leaf<KeyType, ElementType, order>
{
	B_Node():
};