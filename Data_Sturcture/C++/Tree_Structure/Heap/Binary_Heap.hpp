#pragma once

#include <iostream>

#define Debug // IF Run Unit Test, Enable this

enum Direction : bool
{
	Left,
	Right
};

/// ============================================================================================================
/// https://www.cnblogs.com/sybil
/// 二叉堆父子下标关系推导(0开始)
/// ============================================================================================================

/// @brief 仅实现顺序堆
/// @tparam ElementType
/// @tparam CompareMethod 元素比较的函数对象。以根所为比较：如greater表示大根堆，less表示小根堆
/// @note 顺序数组存储，父子节点满足	child:[i]->[2i+1,2i+2],parent:[i]->[(i-1)/2]
template <typename ElementType, size_t maxsize, typename CompareMethod = std::less<>>
class Binary_Heap
{
public:
	ElementType storage[maxsize]{}; // 存放排序关键值的数组
	size_t size{};

public:
	// 初始化有maxsize个元素空间的二叉堆
	Binary_Heap()
	{
		static_assert(maxsize > 0, "Maxsize must be greater than 0");
	}
	Binary_Heap(const Binary_Heap<ElementType, maxsize, CompareMethod> &other)
		: size(other.size)
	{
		for (size_t i = 0; i < size; i++)
			storage[i] = other.storage[i];
	}
	Binary_Heap<ElementType, maxsize, CompareMethod> &
	operator=(const Binary_Heap<ElementType, maxsize, CompareMethod> &other)
	{
		if (this == &other)
			throw std::logic_error("Slef Copied");
		size = other.size;
		for (size_t i = 0; i < size; i++)
			storage[i] = other.storage[i];
		return *this;
	}
	Binary_Heap(Binary_Heap<ElementType, maxsize, CompareMethod> &&other)
		: size(other.size)
	{
		for (size_t i = 0; i < size; i++)
		{
			storage[i] = std::move(other.storage[i]);
			other.storage[i] = ElementType{};
		}
		other.size = 0;
	}
	Binary_Heap<ElementType, maxsize, CompareMethod> &
	operator=(Binary_Heap<ElementType, maxsize, CompareMethod> &&other)
	{
		if (this == &other)
			throw std::logic_error("Slef Copied");
		size = other.size;
		for (size_t i = 0; i < size; i++)
		{
			storage[i] = std::move(other.storage[i]);
			other.storage[i] = ElementType{};
		}
		return *this;
	}

	Binary_Heap(std::initializer_list<ElementType> list)
	{
		if (list.size() > maxsize)
			throw std::invalid_argument("No Enough Space");

		for (const auto &element : list)
			Push(element);

		/// ============================================================================================================
		// 以上是最简单的实现方式，也可以直接进行堆排序，然后再赋值给数组,暂不演示
		/// ============================================================================================================
	}

private:
	// 下标->位序
	constexpr size_t _Position(size_t index) { return ++index; }
	// 位序->下标
	constexpr size_t _Index(size_t index) { return --index; }

	/// @brief 传入下标，交换堆中两个元素
	void _Element_Swap(size_t index_x, size_t index_y)
	{
		if (index_x < 0 || index_x >= size)
			throw std::runtime_error("X illegal");
		if (index_y < 0 || index_y >= size)
			throw std::runtime_error("Y illegal");

		ElementType temp = std::move(storage[index_x]);
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
		{ /// 若子节点比父节点权重高，交换父子节点
			_Element_Swap(index_parent, index);
			index = index_parent;
			index_parent = index_parent == 0 ? 0 : _Index_Parent(index); /// 循环到index为根节点时，避免抛出异常
		}
	}
	// 将下标为index的元素下潜
	void _Element_Sink(size_t index)
	{

		if (index < 0 || index > size)
			throw std::runtime_error("Element_Sink Failed: index illegal");
		while (_Index_Child(index, Left) < size)
		{
			size_t index_child = _Index_Child(index, Left); /// 先假设索引设为左孩子

			if (index_child + 1 < size && CompareMethod{}(storage[index_child + 1], storage[index_child]))
				++index_child; /// 俩孩子中选出一个权重最高的与父节点比较
			if (CompareMethod{}(storage[index_child], storage[index]))
			{
				_Element_Swap(index_child, index);
				index = index_child;
			}
			else
				break;
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
	size_t _Index_Child(size_t index, Direction direction)
	{
		if (index < 0)
			throw std::runtime_error("Illegal index");
		return (direction == Left) ? index * 2 + 1 : index * 2 + 2;
	}

public:
	// 清空所有元素
	void Clear()
	{
		while (!Is_Empty())
			Pop();
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
	constexpr size_t Get_Size() const { return size; }
	constexpr size_t Is_Empty() const { return size == 0; }
	bool operator==(const Binary_Heap<ElementType, maxsize, CompareMethod> &other)
	{
		if (size != other.size)
			return false;
		for (size_t i = 0; i < size; i++)
		{
			if (storage[i] != other.storage[i])
				return false;
		}
		return true;
	}

public:
	// 返回堆顶元素
	constexpr ElementType &Get_Top() { return storage[0]; }
	// 在二叉堆中插入元素key
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

	// 删除堆顶元素
	void Pop()
	{
		if (size < 1)
			throw std::runtime_error("Extract Failed: Heap is empty");
		if (size != 1)									  // 一个元素时堆顶==末尾元素，会造成自我拷贝，所以直接跳过交换
			Get_Top() = std::move(storage[_Index(size)]); // 尾元素覆盖堆顶
		storage[_Index(size)] = ElementType{};			  // 重置尾元素

		--size; // 先下沉，再减少size
		if (size != 0)
			_Element_Sink(0); /// 被交换的根节点下沉
		return;
	}

#ifdef Debug
public:
	// For Unit Test Only
	bool Check_Heap()
	{
		for (size_t i{}; i < size; ++i)
		{ // 先和右孩子比较，在和左孩子比较。如果左孩子不存在，直接跳过后面所有没有孩子的节点，返回成功
			size_t
				index_child_left{_Index_Child(i, Direction::Left)},
				index_child_right{_Index_Child(i, Direction::Right)};
			if (index_child_right < size)
				if (!CompareMethod{}(storage[i], storage[index_child_right]))
					return false;
			if (index_child_left < size)
				if (!CompareMethod{}(storage[i], storage[index_child_left]))
					return false;
				else
					return true;
		}
		return true;
	}
#endif
};
