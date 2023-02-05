#pragma once





template <typename DataType,typename NodeType>
class Tree_Normal
{
protected:
	NodeType* root;		///根节点指针
	int branch;			///分叉数量上限
	int count;			///节点总数

public:
	Tree_Normal(int branch)
		:branch(branch), count(0) {};
	virtual ~Tree_Normal() = default;

protected:
	bool Tree_CheckEmpty() const
	{return count == 0 ? true : false;}
	//访问节点名
	void Tree_Visit_Name(NodeType* node)
	{
		if (node)
			std::cout << node->name << ' ';
	}

public:
	virtual NodeType* Tree_GetRoot() = 0;
	virtual NodeType* Node_Create(std::string name, DataType element = 0)
	{
		NodeType* node = new NodeType(name, element);
		return node;
	}
	///只能在初始化的时候使用
	virtual void Tree_Set_Root(NodeType* root) = 0;
	virtual void Node_Insert(NodeType* node, NodeType* parent, int position) = 0;
	//先根遍历 = 二叉树先序遍历
	virtual void Tree_Traverse_PreOrder(NodeType* node) = 0;
	//后根遍历 = 二叉树中序遍历
	virtual void Tree_Traverse_PostOrder(NodeType* node) = 0;
	//层次遍历
	virtual void Tree_Traverse_LevelOrder(NodeType* node) = 0;
	virtual void Tree_Show() = 0;
};