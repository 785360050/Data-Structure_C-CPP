#pragma once



template <typename DataType>
struct TreeNode
{
	std::string name;
	DataType element;
};





/*

template <typename NodeType, typename DataType>
class Binary_Tree// :public DataStructure
{
public:
	//初始化树
	//virtual void Tree_Init() = 0;
	//销毁树
	virtual void Tree_Destroy() = 0;
	//创建种类为TreeType的树
	//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
	virtual void Tree_Create_Type() = 0;
	//清空树
	virtual void Tree_Clear() = 0;
	//判断是否树空
	virtual void Tree_CheckEmpty() = 0;
	//返回树深度
	virtual void Tree_GetDepth() = 0;
	//返回树根
	virtual void Tree_GetRoot() = 0;
	//显示树所有信息
	virtual void Tree_Show() = 0;
	//返回树中节点node的元素值
	virtual void Node_GetElement(NodeType node) = 0;
	//将树中节点node的元素值为data
	virtual void Node_SetElement(NodeType node, DataType data) = 0;
	//返回节点node的双亲节点
	virtual void Node_GetParent(NodeType node) = 0;
	//返回节点node的左孩子节点
	virtual void Node_GetChild_Left() = 0;
	//返回节点node的右边兄弟节点
	virtual void Node_GetSibling_Right() = 0;
	//将节点node作为第x个孩子插入到子树tree中
	virtual void Node_Insert() = 0;//???
	//删除当前节点的第x个子树
	virtual void Node_Delete() = 0;//???

public:
	//返回节点node的右孩子节点
	virtual void Node_GetChild_Right() = 0;
	//返回节点node的左边兄弟节点
	virtual void Node_GetSibling_Left() = 0;
	//前序遍历二叉树	DLR
	virtual void Tree_Traverse_PreOrder() = 0;///
	//前序遍历二叉树	LDR
	virtual void Tree_Traverse_InOrder() = 0;///
	//前序遍历二叉树	LRD
	virtual void Tree_Traverse_PostOrder() = 0;///
	//层次遍历二叉树
	virtual void Tree_Traverse_LevelOrder() = 0;///



public:
	void Tree_Destroy_SubTree(NodeType* node);
};


*/







