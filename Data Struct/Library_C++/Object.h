#pragma once

//TODO: 同类下的不同变种存储用继承来实现

class DataStructure
{
public:
private:
	//Liner_Structure;
	//Tree;
	//Graph;
};

template <typename DataType>
class Liner_List
{///ADT 
	//初始化线性表
	virtual void List_Init(int maxsize) = 0;
	//销毁线性表
	virtual void List_Destroy() = 0;
	//清空线性表
	virtual void List_Clear() = 0;
	//判断是否表空
	virtual bool List_CheckEmpty() = 0;
	//返回表长(元素个数)
	virtual int List_GetLenghth() = 0;
	//返回第pos个元素的元素值
	virtual DataType List_GetElement(int pos) = 0;
	//显示线性表所有信息
	virtual void List_Show(const char* string) = 0;

	//插入元素
	virtual void Element_Insert(int pos, DataType elem) = 0;
	//删除元素
	virtual void Element_Delete(int pos, DataType& elem) = 0;

	/*链表派生
	//定位并返回元素值为element的元素
	virtual void Element_Locate() = 0;//链表
	//返回目标元素的前驱
	virtual void Element_Prior() = 0;//链表
	//返回目标元素的后继
	virtual void Element_Next() = 0;//链表
	*/
};



template <typename DataType>
struct Stack
{
	//初始化栈
	virtual void Stack_Init() = 0;
	//销毁栈
	virtual void Stack_Destroy() = 0;
	//清空栈
	virtual void Stack_Clear() = 0;
	//判断是否栈空
	virtual void Stack_CheckEmpty() = 0;
	//返回栈长度(元素个数)
	virtual void Stack_Length() = 0;
	//返回栈顶元素
	virtual void Stack_GetTop() = 0;

	//元素入栈
	virtual void Element_Push(DataType element) = 0;
	//元素出栈
	virtual void Element_Pop(DataType element) = 0;

};

template<typename DataType>
struct Queue
{
	//初始化队列
	virtual void Queue_Init() = 0;
	//销毁队列
	virtual void Queue_Destroy() = 0;
	//清空队列
	virtual void Queue_Clear() = 0;
	//判断是否队空
	virtual void Queue_CheckEmpty() = 0;
	//返回队列长度(元素个数)
	virtual void Queue_Length() = 0;
	//返回队头
	virtual void Queue_GetHead() = 0;
	//显示整个队列信息
	virtual void Queue_Show() = 0;
	//元素入队
	virtual void Element_Enqueue() = 0;
	//元素出队
	virtual void Element_Dequeue() = 0;
};

template <typename NodeType,typename DataType>
class Tree_Structure// :public DataStructure
{
public:
	//初始化树
	virtual void Tree_Init() = 0;
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
	virtual void Node_SetElement(NodeType node,DataType data) = 0;
	//返回节点node的双亲节点
	virtual void Node_GetParent(NodeType node) = 0;
	//返回节点node的左孩子节点
	virtual void Node_GetChild_Left() = 0;
	//返回节点node的右边兄弟节点
	virtual void Node_GetBrother_Right() = 0;
	//将节点node作为第x个孩子插入到子树tree中
	virtual void Node_Insert() = 0;//???
	//删除当前节点的第x个子树
	virtual void Node_Delete() = 0;//???



	
};

class Graph// :public DataStructure
{
	/// <summary>
	/// 数据对象：Vertex
	///		顶点集合，具有相同特性的数据元素的集合
	/// 数据关系：Vertex Arc ???
	/// </summary>
	Graph();
	//初始化图
	virtual void Graph_Create() = 0;
	//销毁图
	virtual void Graph_Destroy() = 0;
	//返回节点元素值
	virtual void Graph_GetVertex() = 0;
	//返回顶点vertex的邻接顶点
	virtual void Graph_GetAdjacentVertex_First() = 0;
	//返回顶点vertex的下一个邻接节点
	virtual void Graph_GetAdjacentVertex_Next() = 0;
	//深度优先遍历
	virtual void Graph_Traverse_DFS() = 0;
	//广度优先遍历
	virtual void Graph_Traverse_BFS() = 0;
	//定位并返回顶点v
	virtual void Vertex_Locate() = 0;
	//设置元素vertex值为data
	virtual void Vertex_Set() = 0;
	//插入顶点
	virtual void Vertex_Insert() = 0;
	//删除顶点
	virtual void Vertex_Delete() = 0;
	//对两个顶点添加弧
	virtual void Arc_Insert() = 0;
	//删除两个顶点之间的弧
	virtual void Arc_Delete() = 0;
};




