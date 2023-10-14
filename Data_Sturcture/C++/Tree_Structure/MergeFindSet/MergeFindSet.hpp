#pragma once

#include <iostream>

#include "ADT.hpp"

/// ============================================================================================================
// 2种实现
/// ============================================================================================================
// 1.Quick Find		利用顺序存储实现
// 	查找效率：O(1)
// 	合并效率：O(N)
// 2.Quick Union		利用链式存储实现
// 	查找效率：O(logN)
// 	合并效率：O(logN)
/// ============================================================================================================

namespace Logic
{

	template <typename DataType>
	class MergeFindSet
	{
	protected:
		DataType *element; // 元素集合
		int count;		   // 集合中元素个数

	public:
		MergeFindSet() : element{nullptr}, count(0){};
		MergeFindSet(int maxsize)
			: element{new DataType[maxsize]{}}, count(0){};
		MergeFindSet(int *element_array, int maxsize)
			: element{element_array}, count(maxsize){};
		virtual ~MergeFindSet()
		{
			if (element)
				delete[] element;
			std::cout << "MergeFindSet Destroyed" << std::endl;
		}

	protected:
		// 寻找值为data的元素，在数组中的下标索引

		/// @brief 循环遍历寻找值为data的元素的双亲parents,
		// 直到找到双亲ID == 自己ID的节点，即为data元素所在集合的RootID
		/// @return 根节点ID，失败返回-1
		int Index(DataType data)
		{ /// 遍历找值为data的元素，返回该元素下标

			for (int i = 0; i < count; ++i)
			{
				if (this->element[i] == data)
					return i;
			}
			return -1;
		}
		// int Index(const DataType &data)
		// { /// 遍历找值为data的元素，返回该元素下标

		// 	for (int i = 0; i < count; ++i)
		// 	{
		// 		if (this->element[i] == data)
		// 			return i;
		// 	}
		// 	return -1;
		// }

	public:
		// 判断查并集set中，元素x,y是否再同一个集合中
		virtual bool Find(DataType x, DataType y) = 0;
		// 合并查并集set中元素x,y到同一集合中(x加入y的组)
		virtual void Merge(DataType x, DataType y) = 0;
		// 显示整个查并集
		virtual void Show() = 0;
	};

}
