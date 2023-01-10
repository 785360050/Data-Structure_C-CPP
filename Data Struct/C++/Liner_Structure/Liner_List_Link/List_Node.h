#pragma once
#include <iostream>
using std::cout, std::endl;

//基类链表节点
template<typename DataType>
class List_Node
{
public:
	DataType element;
public:
	List_Node() 
		:element{ NULL }{};
	List_Node(DataType element)
		:element{ element }{};
	virtual void Show() = 0;
};


//单链节点
template<typename DataType>
class List_Node_SingleWay:public List_Node<DataType>
{
public:
	List_Node_SingleWay<DataType>* next = nullptr;
public:
	List_Node_SingleWay()
		:List_Node<DataType>() {};
	List_Node_SingleWay(DataType element, List_Node_SingleWay<DataType>* next = nullptr)
		:List_Node<DataType>(element), next{ next } {};
	void Show()
	{cout<<"Single"<<endl; }
};


//双链节点
template<typename DataType>
class List_Node_DoubleWay:public List_Node<DataType>
{
public:
	List_Node_DoubleWay<DataType>* pre;
	List_Node_DoubleWay<DataType>* next;
public:
	List_Node_DoubleWay() 
		:List_Node<DataType>(), pre{ nullptr }, next{ nullptr } {};
	List_Node_DoubleWay(DataType element, List_Node_DoubleWay<DataType>* pre = nullptr, List_Node_DoubleWay<DataType>* next = nullptr)
		:List_Node<DataType>(element), pre{ pre }, next{next} {};
	void Show()
	{cout<<"Double"<<endl; }
};