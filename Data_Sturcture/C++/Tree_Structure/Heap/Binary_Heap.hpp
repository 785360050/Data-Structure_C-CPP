#pragma once

#include <iostream>
enum Direction { left = 1, right = 2 };


/// <summary>
/// https://www.cnblogs.com/sybil-hxl/p/15088324.html
/// 二叉堆父子下标关系推导(0开始)
/// </summary>
/// <typeparam name="ElementType"></typeparam>

// enum Property { large = 1, small };


/// @brief 仅实现顺序堆
/// @tparam ElementType 
/// @tparam CompareMethod 元素比较的函数对象。以根所为比较：如greater表示大根堆，less表示小根堆
template <typename ElementType,size_t maxsize,typename CompareMethod=std::less<>>
class Binary_Heap
{///顺序数组存储，父子节点满足	child:[i]->[2i+1,2i+2],parent:[i]->[(i-1)/2]
protected:
	// enum Direction bool { left,right };

public:
	ElementType storage[maxsize]{}; // 存放排序关键值的数组
	size_t size{};
public:
	//初始化有maxsize个元素空间的二叉堆
	Binary_Heap()
	{
		static_assert(maxsize > 0, "Maxsize must be greater than 0");
	}

private:
	// 下标->位序
	constexpr size_t _Position(size_t index) { return ++index; }
	// 位序->下标
	constexpr size_t _Index(size_t index) {return --index;}
	
	/// @brief 传入下标，交换堆中两个元素
	void _Element_Swap(size_t index_x, size_t index_y)
	{
		if (index_x < 0 || index_x >= size)
			throw std::runtime_error("X illegal");
		if (index_y < 0 || index_y >= size)
			throw std::runtime_error("Y illegal");

		size_t temp = std::move(storage[index_x]);
		storage[index_x] = std::move(storage[index_y]);
		storage[index_y] = std::move(temp);
	}
	// 将下标为index的元素上浮
	void _Element_Upflow(size_t index)
	{
		if (index == 0)
			return;
		if (index < 0 || index >= size)
			throw std::runtime_error("Element_Upflow Failed: index illegal");
		size_t index_parent = _Index_Parent(index);
		while (index > 0 && CompareMethod{}(storage[index], storage[index_parent]))
		{///若子节点比父节点权重高，交换父子节点
			_Element_Swap(index_parent, index);
			index = index_parent;
			index_parent = index_parent == 0 ? 0 : _Index_Parent(index); /// 循环到index为根节点时，避免抛出异常
		}
	}
	// 将下标为index的元素下潜
	void _Element_Sink(size_t index)
	{
		if (index < 0 || index >= size)
			throw std::runtime_error("Element_Sink Failed: index illegal");
		while (_Index_Child(index, left) < size)
		{
			size_t index_child = _Index_Child(index, left); /// 先假设索引设为左孩子

			if (index_child + 1 < size&&CompareMethod{}(storage[index_child + 1], storage[index_child]))
				++index_child; /// 俩孩子中选出一个权重最高的与父节点比较
			if (CompareMethod{}(storage[index_child], storage[index]))
				break; /// 父节点比所有孩子权重高，取消交换
			_Element_Swap(index_child, index);
			index = index_child;
		}
	}

	/// @brief 返回下标为index的元素的父节点下标
	size_t _Index_Parent(size_t index)
	{
		if (index < 1)
			throw std::runtime_error("Parent is not exsist");
		return (index - 1) / 2;
	}
	/// @brief 返回下标为index的元素的孩子下标
	/// @param direction 左/右孩子
	size_t _Index_Child(size_t index,Direction direction)
	{
		if (index < 0)
			throw std::runtime_error("Illegal index");
		return (direction == left) ? index * 2 + 1 : index * 2 + 2;
	}

public:
	//返回堆顶元素
	constexpr ElementType& Get_Top() {return storage[0]; }
	//在二叉堆中插入元素key
	void Push(const ElementType &element)
	{
		if (size >= maxsize)
			throw std::runtime_error("Insert Failed: Heap is full");
		size++;
		this->storage[_Index(size)] = element;
		_Element_Upflow(_Index(size));
	}
	void Push(ElementType &&element)
	{
		if (size >= maxsize)
			throw std::runtime_error("Insert Failed: Heap is full");
		size++;
		this->storage[_Index(size)] = std::move(element);
		_Element_Upflow(_Index(size));
	}

	//删除堆顶元素
	void Pop()
	{
		if (size < 1)
			throw std::runtime_error("Extract Failed: Heap is empty");
		// Element_Swap(0, Index(size));///首位互换，再下沉
		Get_Top() = std::move(storage[_Index(size)]); // 直接覆盖
		storage[_Index(size)] = ElementType{};
		--size;///堆长度-1代替删除
		_Element_Sink(0);///被交换的根节点下沉
		return ;
	}
	void Heap_Show()
	{
		std::cout
			<< "Length:" << size << std::endl
			<< "index end:" << size << std::endl
			<< "Maxsize:" << maxsize << std::endl;
		for (size_t i = 0; i < maxsize; i++)
			std::cout << "[" << i << ':' << storage[i] << "] ";
		std::cout << std::endl;
	}
	constexpr size_t Size() { return size; }
	constexpr size_t Is_Empty() { return size==0; }
};

























