#pragma once


#include <vector>

#include "../../TreeNode_HighOrder.hpp"
//单链节点
template<typename DataType>
class TreeNode_HighOrder_Child :public TreeNode_HighOrder<DataType>
{
public:
	std::vector<int> children;
	int length;	///当前节点孩子个数
public:
	TreeNode_HighOrder_Child(std::string name, DataType element = NULL)
		:TreeNode_HighOrder<DataType>(name, element),length(0) {};
};

#include <array>
#include <bitset>

inline size_t num{};
template <typename DataType,int branch>
class TreeNode_HighOrder_Child_Ordered : public TreeNode_HighOrder<DataType>
{
public:
	size_t id;							// 用于标记孩子节点的索引
	std::array<int, branch> children{}; //
	std::bitset<branch> control{};//标记第n个孩子是否存在

public:
	TreeNode_HighOrder_Child_Ordered(std::string name, DataType element = DataType{})
		: TreeNode_HighOrder<DataType>(name, element),id{num++} {};
	void Add_Child(size_t child_index,int position)
	{
		if(position<=0 or position>branch)
			throw std::logic_error("position illegal: "+std::to_string(position));

		--position;
		children[position] = child_index;
		control.set(position, true);
	}
	void Delete_Child(int position)
	{
		if (position < 0 or position >= branch)
			throw std::logic_error("position illegal");

		--position;
		children[position] = int{};
		control.set(position, false);
	}
	bool Has_Child(int position) const { return control[position]; }
};
