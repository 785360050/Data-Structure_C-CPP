#pragma once

template<typename DataType>
struct B_Node
{
	DataType* key;			///存放关键字
	int length;			///节点当前元素个数
	int order;			///节点阶数
	B_Node** index;		///存放指针索引
	B_Node* parent;		///父节点
	B_Node(int order)
		:order(order), length{ 0 }, parent{ nullptr }
	{
		try
		{
			if (order < 2)
				throw std::runtime_error("Order must be greater than 2");
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		key = new int[order] {};		///order-1个元素用于存储，最后一个元素空间用于预存,如插入时预存分割元素
		index = new B_Node * [order];
		for (int i = 0; i < order; i++)
			index[i] = nullptr;
	}
};