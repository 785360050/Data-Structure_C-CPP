#pragma once



#include "../B_Node.hpp"
#include "../Tree_B.hpp"
#include "../../../../../Linear_Structure/Linear_List/Linear_List_Link/Link_List.hpp"

template <typename DataType, typename NodeType = B_Node<DataType>>
class B_Plus
{
private:
	using Result = Tree_Advanced_B::Result;
private:
	Tree_Advanced_B<DataType>* root;
	int order;		///阶数
	Link_List_Double<DataType> list;
	Tree_Advanced_B<DataType> node_index;
public:
	B_Plus(int order) :order(order),root(nullptr) {};
	~B_Plus() = default;
public:
	//查找
	Result B_Tree_Search(int key)
	{
		NodeType* precursor = nullptr;	///父节点索引
		NodeType* current = root;	///当前节点索引
		int pos = 0;		///节点中的位置下标
		bool tag{ false };///标记查找状态
		while (current && !tag)
		{///搜索当前节点是否存在目标key
			pos = B_Tree_Node_Locate(current, key);
			if (pos < current->length && current->key[pos] == key)
				///查找成功
				tag = true;
			else
			{///查找失败
				precursor = current;
				current = current->index[pos];	///向下层节点找key(大值的左指针)
			}
		}

		Result result;	///生成结果
		if (tag)
		{///查找成功(树中存在值为key的节点元素)
			result.tag = true;
			result.index = current;
			result.pos = pos;
		}
		else
		{
			result.tag = false;
			result.index = precursor;
			result.pos = pos;
		}
		return result;
	}

	//插入关键字
	void B_Tree_Insert(int key)
	{
		


		/// 定位待插入节点及下标位置
		Result res = B_Tree_Search(key);
		try
		{
			if (res.tag == true)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Insert Failed: key exsisted" << std::endl;
			return;
		}

		NodeType* node = res.index;		///元素插入的节点，此处因为Result搜索失败，所以返回查找节点的父节点声明为parent(即插入节点)
		int pos_node = res.pos;			///元素插入的节点的下标索引pos位置插入元素key(pos=第一个大元素的下标位置)
		NodeType* child = nullptr;		///分裂的新节点

		bool loop = true;				///控制插入的while大循环,完成后控制退出
		bool root_new = false;			///控制分裂时，是否需要新建上层节点
		int key_insert = key;			///插入的key

		if (node)
		{///插入目标节点存在时
			while (loop && !root_new)
			{///key插入当前节点
				{///插入节点
					int i = node->length;
					if (i != node->length)
					{///插入到末尾元素位置不后移，直接覆盖
						for (i; i >= pos_node; --i)
						{///顺序表元素后移插入
							node->key[i] = node->key[i - 1];
							node->index[i + 1] = node->index[i];
						}
					}
					node->key[pos_node] = key_insert;
					node->index[pos_node + 1] = child;
					if (child)
						child->parent = node;
					++node->length;
				}
				///插入后判断是否分裂
				if (node->length < order)
					loop = false;
				else
				{///节点满，分裂
					int pos_mid = order / 2;	///分裂为上层节点
					std::pair<int, NodeType*> pair;
					///分割满节点为两个节点，返回待插入的key
					pair = split(node, pos_mid);
					key_insert = pair.first;
					child = pair.second;
					if (node->parent)
					{///上层节点存在时，key插入到上层节点parent中
						node = node->parent;
						pos_node = B_Tree_Node_Locate(node, key_insert);
					}
					else
						root_new = true;	///需要新建上层节点
				}
			}
		}
		else
		{///插入目标节点不存在时(即空树时)
			NodeType* r = B_Tree_Create_Node(order);///创建上层节点
			root = r;
			r->key[0] = key;
			++r->length;
		}
		if (root_new)
		{
			NodeType* root = B_Tree_Create_Node(order);///创建上层节点
			this->root = root;
			root->key[0] = key_insert;
			root->index[0] = node;
			root->index[1] = child;
			node->parent = root;
			child->parent = root;
			root->length++;
		}
		count++;

	}

	//删除值为key的元素
	void B_Tree_Delete(int key)
	{
		Result result = B_Tree_Search(key);
		if (result.tag)
		{///result查找key成功时，返回key所在的节点和下标
			Delete(result.index, result.pos);
			--count;
		}
		else
			std::cout << "key is not exist" << std::endl;
	}
	//中序遍历
	void B_Tree_Traverse_Inorder(NodeType* node)
	{
		if (node)
		{
			for (int i = 0; i < node->length; ++i)
			{
				if (node->index[i])	///感觉多余
					B_Tree_Traverse_Inorder(node->index[i]);
				///——————————————————————————————————递归分割
				std::cout << node->key[i] << ' ';
			}///补齐缺少的最后一个索引
			B_Tree_Traverse_Inorder(node->index[node->length]);
		}
	}

	///中序遍历并显示信息
	void B_Tree_Show(std::string string)
	{
		std::cout << string << std::endl;
		B_Tree_Traverse_Inorder(root);
		std::cout << std::endl;

	}
};



