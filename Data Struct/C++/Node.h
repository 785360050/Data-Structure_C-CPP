#pragma once

template<typename DataType>
class Node
{
public:
	DataType element;
public:
	Node()
		:element{ NULL } {};
	Node(DataType element)
		:element{ element } {};
	//virtual void Show() = 0;
	//DataType Get_Element()
	//{return element;}
};
