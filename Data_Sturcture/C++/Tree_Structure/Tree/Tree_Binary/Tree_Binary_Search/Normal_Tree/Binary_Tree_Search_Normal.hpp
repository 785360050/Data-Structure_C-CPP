#pragma once

#include "../../Tree_Binary_Normal/Tree_Binary_Normal.hpp"
#include "../Tree_Binary_Search.hpp"
#include "Node_Binary_Search_Normal.hpp"

template <typename DataType, typename KeyType = int, typename NodeType = Node_Binary_Search_Normal<DataType, KeyType>>
class Tree_Binary_Search_Normal : public Tree_Binary_Search<DataType, KeyType, NodeType>
{
public:
	Tree_Binary_Search_Normal() :Tree_Binary_Search<DataType, KeyType, NodeType>() {};
	~Tree_Binary_Search_Normal() = default;

protected:
	NodeType* insertnode(NodeType* node, KeyType key, DataType data = NULL)
	{
		if (!node)
		{
			NodeType* p = this->Node_Create(key, std::to_string(key), data);
			++this->count;
			return p;
		}
		if (key < node->key)
		{
			node->left = insertnode(node->left, key, data);
		}
		else if (key > node->key)
		{
			node->right = insertnode(node->right, key, data);
		}
		else
			std::cout << "Insert failed: Existed" << std::endl;
		return node;
	}
	NodeType* deletenode(NodeType* tree, KeyType key)
	{///删除子树tree中值为data的节点
		/// [此处用逻辑后继顶替]
		if (tree == nullptr)///递归出口
			return nullptr;
		if (key < tree->key)
		{///第2-4个if用于寻路，找到删除目标节点
			tree->left = deletenode(tree->left, key);
			return tree;
		}
		if (key > tree->key)
		{
			tree->right = deletenode(tree->right, key);
			return tree;
		}
		///删除节点，找代替节点
		if (key == tree->key)
		{///此时位于删除节点处，删除节点并调整二叉搜索树
			if (tree->left == NULL && tree->right == NULL)
			{///前两个if处理单孩子情况
				delete tree;
				return nullptr;
			}
			if (tree->left == nullptr)
			{
				NodeType* temp = tree->right;
				delete tree;
				return temp;
			}
			if (tree->right == nullptr)
			{
				NodeType* temp = tree->left;
				delete tree;
				return temp;
			}
			else///左右子树都不为空
			{///用右孩子的最小节点代替(逻辑后继)
				NodeType* p = this->Element_Next(tree);
				tree->replace_by(p);///直接用顶替的节点先覆盖
				tree->right = deletenode(tree->right, p->key);///再删除顶替节点
				return tree;
			}
		}
	}
public:
	void Element_Insert(KeyType key, DataType element = DataType{}) override
	{
		this->root = insertnode(this->root, key, element);
	}
	void Element_Insert_NonRecursive(KeyType key, DataType data = DataType{})
	{
		NodeType* current = this->root, * precursor = nullptr;
		while (current)
		{
			precursor = current;
			if (key == current->key)
			{
				std::cout << "Insert failed: Existed" << std::endl;
				return;
			}
			if (key < current->key)
				current = current->left;
			else
				current = current->right;
		}
		//NodeType* node = new NodeType(std::to_string(data), data);
		NodeType* node = this->Node_Create(key, std::to_string(key), data);
		++this->count;
		if (precursor && key < precursor->key)
			precursor->left = node;
		else if (precursor && key > precursor->key)
			precursor->right = node;
		if (!precursor) 
			this->root = node;
	}

	void Element_Delete(KeyType key) override
	{
		deletenode(this->root, key);
	}

	void DFS(NodeType *node, std::stack<NodeType *>& stack,size_t& level)
	{
		if (!node)
		{
			level = std::max(level, stack.size());
			return;
		}
		stack.push(node);
		DFS(node->left, stack, level);
		DFS(node->right, stack, level);
		stack.pop();
	};
	int Get_Depth(NodeType* node)
	{
		std::stack<NodeType *> stack;
		size_t level{};

		DFS(node, stack, level);
		return level;
	}
};


