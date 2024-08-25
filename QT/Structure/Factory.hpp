#pragma once


#include "Structure.hpp"


#include "Linear_Structure/Stack.hpp"
#include "Linear_Structure/Queue.hpp"
#include "Linear_Structure/Skip_List.hpp"
#include "Tree_Structure/Search_Tree.hpp"
#include "Tree_Structure/AVL_Tree.hpp"
#include "Tree_Structure/Red_Black_Tree.hpp"
#include "Tree_Structure/Heap.hpp"
#include "../Demo/View_Binary_Tree.hpp"
#include "../Demo/View_Tree.hpp"

namespace Factory
{
	class Factory
	{
	public:
		virtual Structure* Produce()=0;
	};

	class Stack:public Factory
	{
	public:
		Structure* Produce() override final {return new View::Stack;}
	};
	class Queue:public Factory
	{
	public:
		Structure* Produce() override final {return new View::Queue;}
	};
	class Skip_List:public Factory
	{
	public:
		Structure* Produce() override final {return new View::Skip_List;}
	};
	class Search_Tree:public Factory
	{
	public:
		Structure* Produce() override final {return new View::Search_Tree;}
	};
	class AVL_Tree:public Factory
	{
	public:
		Structure* Produce() override final {return new View::AVL_Tree;}
	};
	class Tree_Binary_Search_RBT:public Factory
	{
	public:
		Structure* Produce() override final {return new View::Tree_Binary_Search_RBT;}
	};
	class Heap:public Factory
	{
	public:
		Structure* Produce() override final {return new View::Heap;}
	};
	class Tree:public Factory
	{
	public:
		Structure* Produce() override final {return new View::Tree<int,2>;}
	};
	class Binary_Tree:public Factory
	{
	public:
		Structure* Produce() override final {return new View::Binary_Tree;}
	};
}


