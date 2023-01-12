#pragma once


template <typename NodeType, typename DataType>
class Tree_Structure// :public DataStructure
{
	virtual Tree_Structure() = default;
public:
	//创建种类为TreeType的树
	//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
	virtual void Tree_Create_Type() = 0;
	//清空树
	virtual void Tree_Clear() = 0;
	//判断是否树空
	virtual void Tree_CheckEmpty() const = 0;
	//返回树深度
	virtual void Tree_GetDepth() const = 0;
	//返回树根
	virtual void Tree_GetRoot() const = 0;
	//显示树所有信息
	virtual void Tree_Show() const = 0;
	//返回树中节点node的元素值
	virtual void Node_GetElement(NodeType node) const = 0;
	//将树中节点node的元素值为data
	virtual void Node_SetElement(NodeType node, DataType data) = 0;
	//返回节点node的双亲节点
	virtual void Node_GetParent(NodeType node) const = 0;
	//返回节点node的左孩子节点
	virtual void Node_GetChild_Left() const = 0;
	//返回节点node的右边兄弟节点
	virtual void Node_GetBrother_Right() const = 0;
	//将节点node作为第x个孩子插入到子树tree中
	virtual void Node_Insert() = 0;//???
	//删除当前节点的第x个子树
	virtual void Node_Delete() = 0;//???

};