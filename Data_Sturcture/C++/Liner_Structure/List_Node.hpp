#pragma once
#include <iostream>
#include "../Node.h"
using std::cout, std::endl;





//单链节点
template<typename DataType>
class List_Node_SingleWay:public Node<DataType>
{
public:
	List_Node_SingleWay<DataType>* next = nullptr;
public:
	List_Node_SingleWay()
		:Node<DataType>() {};
	List_Node_SingleWay(DataType element, List_Node_SingleWay<DataType>* next = nullptr)
		:Node<DataType>(element), next{ next } {};
	void Show()
	{cout<<"Single"<<endl; }
};


//双链节点
template<typename DataType>
class List_Node_DoubleWay:public Node<DataType>
{
public:
	List_Node_DoubleWay<DataType>* pre;
	List_Node_DoubleWay<DataType>* next;
public:
	List_Node_DoubleWay() 
		:Node<DataType>(), pre{ nullptr }, next{ nullptr } {};
	List_Node_DoubleWay(DataType element, List_Node_DoubleWay<DataType>* pre = nullptr, List_Node_DoubleWay<DataType>* next = nullptr)
		:Node<DataType>(element), pre{ pre }, next{next} {};
	void Show()
	{cout<<"Double"<<endl; }
};