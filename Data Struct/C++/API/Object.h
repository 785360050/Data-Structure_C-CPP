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

template <typename NodeType, typename DataType>
class Liner_Structure// :public DataStructure
{
	virtual void List_Init() = 0;
	virtual void List_Clear() = 0;
	virtual void List_Destroy() = 0;
	virtual bool List_CheckEmpty() = 0;
	virtual int List_GetLength() = 0;
	virtual void List_Show(const char* string) = 0;

	//定位节点
	virtual NodeType* Element_Locate(int pos) = 0;
	virtual NodeType* Element_Prior(const NodeType* const node) = 0;
	virtual NodeType* Element_Next(const NodeType* const node) = 0;
	virtual void Element_Insert(int pos, DataType element) = 0;
	virtual void Element_Delete(int pos) = 0;
	virtual DataType Element_Show(NodeType* node) = 0;

};///precursor node

class Tree// :public DataStructure
{

};

class Graph// :public DataStructure
{

};




