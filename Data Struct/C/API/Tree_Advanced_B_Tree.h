#pragma once

#include <iostream>

struct B_Node
{
	int* key;			///存放关键字
	int length;			///节点当前元素个数
	int maxsize;		///节点最大元素个数
	B_Node* index;		///存放指针索引
	B_Node* parent;		///
};

struct B_Tree
{///回溯法实现插入删除
	B_Node* root;
	int order;			///B树阶数
	int count;
};








