#pragma once

#include <utility>

/// @brief 节点基类
/// @tparam ElementType 存放的元素类型
/// @note 由于没有设置成员函数获取成员变量值，所以不要改动成员变量命名
template <typename ElementType>
class Node
{
public:
	ElementType element{};

public:
	Node() = default;
	Node(const ElementType &element) : element(element){};
	Node(ElementType &&element) : element(std::move(element)){};
	Node(const Node &other)         : element{other.element} {};
	Node(Node &&other)              : element{std::move(other.element)}
	{
		other.element = ElementType{};
	}
	// copy element
	Node &operator=(const Node &other)
	{
		if(this == &other)
			throw std::runtime_error("Self assignment");
		element = other.element;
		return *this;
	}
	// move element
	Node &operator=(Node &&other)
	{
		element = std::move(other.element);
		other.element = ElementType{};
		return *this;
	}

public:
	bool operator==(const Node &other) const { return element == other.element; }
	auto operator<=>(const Node &other) const { return element <=> other.element; }
};
