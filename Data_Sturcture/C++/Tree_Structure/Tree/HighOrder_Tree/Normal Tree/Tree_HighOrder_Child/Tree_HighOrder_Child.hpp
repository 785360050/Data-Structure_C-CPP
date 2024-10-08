#pragma once

#include <queue>

#include "TreeNode_HighOrder_Child.hpp"
#include "../Normal Tree.hpp"

template <typename DataType, typename NodeType = TreeNode_HighOrder_Child<DataType>>
class Tree_Advanced_Child:public Tree_Normal<DataType,NodeType>
{///孩子表示法
// protected:
public:
	std::vector<NodeType*> vertex;//数组存每个树节点，每个节点以链表方式存所有对应的孩子

private:
	//重置子树所有元素为0
	void Clear(NodeType* node)
	{
		if (!node)
			return;
		while (node->child_first)
		{
			NodeType* del_child = node->child_first;
			node->child_first = del_child->child_first;
			while (del_child->sibling_next)
			{
				NodeType* del_sibling = del_child->sibling_next;
				del_child->sibling_next = del_sibling->sibling_next;
				delete del_sibling;
			}
			delete del_child;
		}
		delete node;
	}
	int Deep(NodeType* node)
	{
		return NULL;
	}
	//返回节点名为name的父节点
	NodeType* Parent(NodeType* node, std::string name)
	{
		NodeType* n = this->root;
		NodeType* parent;
		if (n->left->name == name || n->right->name == name)
			return n;
		if (n->left == NULL && n->right == NULL)
			return NULL;
		parent = Parent(n->left, name);
		if (!parent)
			parent = Parent(n->right, name);
		if (parent == NULL)
		{
			std::cout << "Parent Not Found!" << std::endl;
			return NULL;
		}
		return parent;

	}

public:
	Tree_Advanced_Child(int branch)
		:Tree_Normal<DataType,NodeType>(branch) {};
	~Tree_Advanced_Child()
	{
		for (auto& node : vertex)
			delete node;
	}
public:
	//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
	void Tree_Clear()
	{
		Clear(this->root);
	}
	//返回树深度
	int Tree_GetDepth()
	{
		return Deep(this->root);
	}
	//返回树根节点
	virtual NodeType* Tree_GetRoot()
	{
		return this->root;
	}
	virtual void Tree_Set_Root(NodeType* root)
	{///只能在初始化的时候使用，后续使用count会出错
		this->root = root;
		vertex.push_back(root);
		this->count++;
	}
	//显示树所有信息
	virtual void Tree_Show()
	{
		std::cout << "当前子树节点总数: " << this->count << std::endl
			<< "分叉数: " << this->branch << std::endl;
		std::cout << "[index] [vertex] -> [child_index]" << std::endl;
		for (int i = 0; i < vertex.size(); ++i)
		{
			std::cout << '[' << i << "] " << vertex[i]->name << "->";
			for (const auto& i : vertex[i]->children)
				std::cout << i << "->";
			std::cout << "END" << std::endl;
		}
		std::cout << std::endl;
	}
	//返回树中节点node的元素值
	void Node_GetElement(NodeType* node)
	{
		try
		{
			if (!node)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Get Element Faild: Node is not exist" << std::endl;
			return;
		}
		return node->element;
	}
	//将树中节点node的元素值为element
	void Node_SetElement(NodeType* node, DataType element)
	{
		try
		{
			if (!node)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Set Element Faild: Node is not exist" << std::endl;
			return;
		}
		node->element = element;
	}
	//todo 返回节点node的双亲节点
	//NodeType* Node_GetParent(NodeType* node)
	//{
	//	try
	//	{
	//		if (!node)
	//			throw 1;
	//	}
	//	catch (...)
	//	{
	//		std::cout << "Set Element Faild: Node is not exist" << std::endl;
	//		return NULL;
	//	}
	//	return Parent(node, node->name);
	//}
	//返回节点node的左孩子节点
	///void Node_GetChild_Left() = 0;
	//返回节点node的右边兄弟节点1
	///void Node_GetSibling_Right() = 0;
	//将节点node作为第x个孩子插入到子树tree中
	void Node_Insert(NodeType* node, NodeType* parent, int position)
	{
		try
		{
			if (!node)
				throw std::runtime_error("Node_Insert Failed: node is not exsist");
			if (!parent)
				throw std::runtime_error("Node_Insert Failed: parent is not exsist");
			if (position<1 || position>this->branch)
				throw std::runtime_error("Node_Insert Failed: position illegal");
			if (parent->length >= this->branch)
				throw std::runtime_error("Node_Insert Failed: Parent's Child is full");
			for (const auto& n : vertex)
			{
				if (n == node)
					throw std::runtime_error("Node_Insert Failed: Node already exists");
			}
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		int i;

		for (i = 0; i != vertex.size(); ++i)
		{///定位父节点下标
			if (vertex[i] == parent)
				break;
		}
		vertex.push_back(node);
		if (i != vertex.size())
		{///父节点存在
			vertex[i]->children.push_back(vertex.size() - 1);
		}

		++parent->length;
		this->count++;
	}
	//新建节点(new 分配空间)
	virtual NodeType* Node_Create(std::string name, DataType element = 0)
	{
		NodeType* node = new NodeType(name, element);
		return node;
	}

public:
	//返回节点在vertex中的下标
	int Index(NodeType* node)
	{
		for (int i = 0; i < vertex.size(); ++i)
		{
			if (vertex[i] == node)
				return i;
		}
		return -1;
	}
	//先根遍历
	void Tree_Traverse_PreOrder(NodeType* node)
	{
		static bool* visit_state = new bool[vertex.size()](false);
		if (!node)
			return;
		int index = Index(node);
		if (index != -1 && !visit_state[index])
		{///当前节点存在且为访问过，则输出
			this->Tree_Visit_Name(vertex[index]);
			visit_state[index] = true;
		}
		for (int i = 0; i < node->children.size(); ++i)
			Tree_Traverse_PreOrder(vertex[node->children[i]]);
	}
	//后根遍历
	void Tree_Traverse_PostOrder(NodeType* node)
	{
		static bool* visit_state = new bool[vertex.size()](false);
		if (!node)
			return;
		for (int i = 0; i < node->children.size(); ++i)
			Tree_Traverse_PostOrder(vertex[node->children[i]]);
		int index = Index(node);
		if (index != -1 && !visit_state[index])
		{///当前节点存在且为访问过，则输出
			this->Tree_Visit_Name(vertex[index]);
			visit_state[index] = true;
		}
	}
	//层次遍历
	void Tree_Traverse_LevelOrder(NodeType* node)
	{
		std::queue<NodeType*> queue;
		queue.push(node);
		while (!queue.empty())
		{
			NodeType* p = queue.front();
			for (const auto& i : p->children)
				queue.push(vertex[i]);
			this->Tree_Visit_Name(queue.front());
			queue.pop();

		}
	}

};


#include <optional>
#include <map>
namespace Storage
{
	// 孩子位置关系无序
	template <typename DataType, int branch, typename NodeType = TreeNode_HighOrder_Child<DataType>>
	class Tree_Normal_Child : public Logic::Tree_Normal<DataType, NodeType, branch>
	{///孩子表示法
	// protected:
	public:
		std::vector<NodeType*> vertex;//数组存每个树节点，每个节点以链表方式存所有对应的孩子

	private:
		void Clear(NodeType *node) override
		{
			if (!node)
				return;
			for (const auto& node: vertex) 
				delete node;
		}
		int Deep(NodeType* node)
		{
			return NULL;
		}
		//返回节点名为name的父节点
		NodeType* Parent(NodeType* node, std::string name)
		{
			NodeType* n = this->root;
			NodeType* parent;
			if (n->left->name == name || n->right->name == name)
				return n;
			if (n->left == NULL && n->right == NULL)
				return NULL;
			parent = Parent(n->left, name);
			if (!parent)
				parent = Parent(n->right, name);
			if (parent == NULL)
			{
				std::cout << "Parent Not Found!" << std::endl;
				return NULL;
			}
			return parent;

		}

	public:
		Tree_Normal_Child() : Logic::Tree_Normal<DataType, NodeType, branch>() {};
		~Tree_Normal_Child()
		{
			for (auto& node : vertex)
				delete node;
		}
	public:
		//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
		void Clear() 
		{
			Clear(this->root);
		}
		//返回树深度
		int Get_Depth(NodeType *node) override
		{
			return Deep(this->root);
		}
		virtual void Tree_Set_Root(NodeType* root)
		{///只能在初始化的时候使用，后续使用count会出错
			this->root = root;
			vertex.push_back(root);
			this->count++;
		}
		//显示树所有信息
		virtual void Show() override
		{
			std::cout << "当前子树节点总数: " << this->count << std::endl
				<< "分叉数: " << branch << std::endl;
			std::cout << "[index] [vertex] -> [child_index]" << std::endl;
			for (int i = 0; i < vertex.size(); ++i)
			{
				std::cout << '[' << i << "] " << vertex[i]->name << "->";
				for (const auto& i : vertex[i]->children)
					std::cout << i << "->";
				std::cout << "END" << std::endl;
			}
			std::cout << std::endl;
		}

		//将节点node作为第x个孩子插入到子树tree中
		void Node_Insert(NodeType* node, NodeType* parent, int position)
		{
			try
			{
				if (!node)
					throw std::runtime_error("Node_Insert Failed: node is not exsist");
				if (!parent)
					throw std::runtime_error("Node_Insert Failed: parent is not exsist");
				if (position<1 || position>branch)
					throw std::runtime_error("Node_Insert Failed: position illegal: x ∈ [1," + std::to_string(branch) + "]");
				if (parent->length >= branch)
					throw std::runtime_error("Node_Insert Failed: Parent's Child is full");
				for (const auto& n : vertex)
				{
					if (n == node)
						throw std::runtime_error("Node_Insert Failed: Node already exists");
				}
			}
			catch (const std::runtime_error& e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			int i;

			for (i = 0; i != vertex.size(); ++i)
			{///定位父节点下标
				if (vertex[i] == parent)
					break;
			}
			vertex.push_back(node);
			if (i != vertex.size())
			{///父节点存在
				vertex[i]->children.push_back(vertex.size() - 1);
			}

			++parent->length;
			this->count++;
		}

	public:
		//返回节点在vertex中的下标
		int Index(NodeType* node)
		{
			for (int i = 0; i < vertex.size(); ++i)
			{
				if (vertex[i] == node)
					return i;
			}
			return -1;
		}
		//先根遍历
		void Traverse_PreOrder(NodeType* node) override
		{
			static bool* visit_state = new bool[vertex.size()](false);
			if (!node)
				return;
			int index = Index(node);
			if (index != -1 && !visit_state[index])
			{///当前节点存在且为访问过，则输出
				this->Tree_Visit_Name(vertex[index]);
				visit_state[index] = true;
			}
			for (int i = 0; i < node->children.size(); ++i)
				Traverse_PreOrder(vertex[node->children[i]]);
		}
		//后根遍历
		void Traverse_PostOrder(NodeType *node) override
		{
			static bool* visit_state = new bool[vertex.size()](false);
			if (!node)
				return;
			for (int i = 0; i < node->children.size(); ++i)
				Traverse_PostOrder(vertex[node->children[i]]);
			int index = Index(node);
			if (index != -1 && !visit_state[index])
			{///当前节点存在且为访问过，则输出
				this->Tree_Visit_Name(vertex[index]);
				visit_state[index] = true;
			}
		}
		//层次遍历
		void Traverse_LevelOrder(NodeType *node) override
		{
			std::queue<NodeType*> queue;
			queue.push(node);
			while (!queue.empty())
			{
				NodeType* p = queue.front();
				for (const auto& i : p->children)
					queue.push(vertex[i]);
				this->Tree_Visit_Name(queue.front());
				queue.pop();

			}
		}

	};

	// 孩子位置关系有序
	template <typename DataType, int branch, typename NodeType = TreeNode_HighOrder_Child_Ordered<DataType, branch>>
	// using DataType = bool;
	// static const int branch = 3;
	// using NodeType = TreeNode_HighOrder_Child_Ordered<bool,3>;
	class Tree_Normal_Child_Ordered : public Logic::Tree_Normal<DataType, NodeType, branch>
	{ /// 孩子表示法
		// protected:
	public:
		std::map<size_t, NodeType*> vertex; // <node_id,node>
		// std::vector<NodeType> vertex; // 数组存每个树节点，每个节点以链表方式存所有对应的孩子

	private:
		void Clear(NodeType *node) override
		{
			// if (!node)
			// 	return;
			// for (const auto &node : vertex)
			// 	delete node;
		}
		int Deep(NodeType *node)
		{
			return 0;
		}
		// 返回节点名为name的父节点
		NodeType *Parent(NodeType *node, std::string name)
		{
			NodeType *n = this->root;
			NodeType *parent;
			if (n->left->name == name || n->right->name == name)
				return n;
			if (n->left == NULL && n->right == NULL)
				return NULL;
			parent = Parent(n->left, name);
			if (!parent)
				parent = Parent(n->right, name);
			if (parent == NULL)
			{
				std::cout << "Parent Not Found!" << std::endl;
				return NULL;
			}
			return parent;
		}

	public:
		Tree_Normal_Child_Ordered() : Logic::Tree_Normal<DataType, NodeType, branch>() {};
		~Tree_Normal_Child_Ordered()
		{
			// for (auto &node : vertex)
			// 	delete node;
		}

	public:
		//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
		void Clear()
		{
			Clear(this->root);
		}
		// 返回树深度
		int Get_Depth(NodeType *node) override
		{
			return Deep(this->root);
		}
		virtual void Tree_Set_Root(NodeType *root)
		{ /// 只能在初始化的时候使用，后续使用count会出错
			this->root = root;
			vertex[root->id]= root;
			this->count++;
		}
		// 显示树所有信息
		virtual void Show() override
		{
			std::cout << "当前子树节点总数: " << this->count << std::endl
					  << "分叉数: " << branch << std::endl;
			std::cout << "[index] [vertex] -> [child_index_1][child_index_2]..." << std::endl;
			for (const auto& e: vertex) 
			{
				auto node =e.second;
				std::cout << '[' << node->id << "] " << node->name << " -> ";
				for (int i{}; i < branch;++i)
				{
					std::cout << '[';
					if (node->Has_Child(i))
						std::cout << node->children[i];
					std::cout << "]";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		// 将节点node作为第x个孩子插入到子树tree中
		void Node_Insert(NodeType *node, NodeType *parent, int position) override
		{
			try
			{
				if (!node)
					throw std::runtime_error("Node_Insert Failed: node is not exsist");
				if (!parent)
					throw std::runtime_error("Node_Insert Failed: parent is not exsist");
				if (position < 1 || position > branch)
					throw std::runtime_error("Node_Insert Failed: position illegal: x ∈ [1," + std::to_string(branch) + "]");
				// if (parent->length >= branch)
				// 	throw std::runtime_error("Node_Insert Failed: Parent's Child is full");
				// for (const auto &n : vertex)
				// {
				// 	if (n == node)
				// 		throw std::runtime_error("Node_Insert Failed: Node already exists");
				// }
			}
			catch (const std::runtime_error &e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
			vertex[node->id] = node;
			if (parent and vertex.contains(parent->id)) /// 父节点存在
			{
				parent->Add_Child(node->id, position);
				// node_parent->children[position] = node->id;
			}
			else
				throw std::logic_error("parent node not exist");

			this->count++;
		}
		void Node_Delete(NodeType *node)
		{
			for (const auto& node: vertex) 
			{
				for (int i{}; i < node.children.size();++i)
				{
					if (node.children[i].id == node->id)
						node.Delete_Child(i);
				}
			}
			vertex.erase(node->id);
		}

	public:
		// 先根遍历
		void Traverse_PreOrder(NodeType *node) override
		{
			// static bool *visit_state = new bool[vertex.size()](false);
			// if (!node)
			// 	return;
			// int index = Index(node);
			// if (index != -1 && !visit_state[index])
			// { /// 当前节点存在且为访问过，则输出
			// 	this->Tree_Visit_Name(vertex[index]);
			// 	visit_state[index] = true;
			// }
			// for (int i = 0; i < node->children.size(); ++i)
			// 	Traverse_PreOrder(vertex[node->children[i]]);
		}
		// 后根遍历
		void Traverse_PostOrder(NodeType *node) override
		{
			// static bool *visit_state = new bool[vertex.size()](false);
			// if (!node)
			// 	return;
			// for (int i = 0; i < node->children.size(); ++i)
			// 	Traverse_PostOrder(vertex[node->children[i]]);
			// int index = Index(node);
			// if (index != -1 && !visit_state[index])
			// { /// 当前节点存在且为访问过，则输出
			// 	this->Tree_Visit_Name(vertex[index]);
			// 	visit_state[index] = true;
			// }
		}
		// 层次遍历
		void Traverse_LevelOrder(NodeType *node) override
		{
			// std::queue<NodeType *> queue;
			// queue.push(node);
			// while (!queue.empty())
			// {
			// 	NodeType *p = queue.front();
			// 	for (const auto &i : p->children)
			// 		queue.push(vertex[i]);
			// 	this->Tree_Visit_Name(queue.front());
			// 	queue.pop();
			// }
		}
	};
}