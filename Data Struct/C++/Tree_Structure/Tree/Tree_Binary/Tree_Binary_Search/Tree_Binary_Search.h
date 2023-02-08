#pragma once




template <typename DataType, typename NodeType>
class Binary_Tree_Search
{
protected:
	NodeType* root;
	int count;
public:
	Binary_Tree_Search() :root(nullptr), count(0) {};
	~Binary_Tree_Search() = default;
protected:
	//增加二叉搜索节点data
	virtual NodeType* insertnode(NodeType* node, DataType data)
	{
		if (!node)
		{
			NodeType* p = this->Node_Create(std::to_string(data), data);
			++this->count;
			return p;
		}
		if (data < node->element)
		{
			NodeType* left = insertnode(node->left, data);
			node->left = left;
		}
		else if (data > node->element)
		{
			NodeType* right = insertnode(node->right, data);
			node->right = right;
		}
		else
			std::cout << "Insert failed: Existed" << std::endl;
		return node;
	}
	//删除二叉搜索节点data
	NodeType* deletenode(NodeType* tree, DataType data)
	{///删除子树tree中值为data的节点
		/// [此处用逻辑后继顶替]
		if (tree == nullptr)///递归出口
			return nullptr;
		if (data < tree->element)
		{///第2-4个if用于寻路，找到删除目标节点
			tree->left = deletenode(tree->left, data);
			return tree;
		}
		if (data > tree->element)
		{
			tree->right = deletenode(tree->right, data);
			return tree;
		}
		///删除节点，找代替节点
		if (data == tree->element)
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
				tree->element = p->element;///直接用顶替的节点先覆盖
				tree->name = p->name;
				tree->right = deletenode(tree->right, p->element);///再删除顶替节点
				return tree;
			}
		}
	}
public:
	void Node_Visit_Name(NodeType* node)
	{
		if (node)
		{
			std::cout << node->name << ' ';
		}
	}
	void Tree_Traverse_InOrder(NodeType* node)
	{
		if (node)
		{
			Tree_Traverse_InOrder(node->left);
			this->Node_Visit_Name(node);
			Tree_Traverse_InOrder(node->right);
		}
	}
	NodeType* Tree_GetRoot()
	{
		return root;
	}
	void Tree_Set_Root(NodeType* node)
	{
		try
		{
			if (!node)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Root Init Faild: node is not exists" << std::endl;
			return;
		}
		root = node;
		++count;
	}
	NodeType* Node_Create(std::string name, DataType element = NULL)
	{
		return new NodeType(name, element);
	}

	//查找节点  O(Logn)
	NodeType* Tree_Element_Locate(string name)
	{
		NodeType* p = this->root;
		while (p)
		{
			if (p->name == name)
				return p;
			else
				p = (name < p->name) ? p->left : p->right;
		}
		return nullptr;
	}

	void Tree_Element_Insert(DataType data)
	{
		insertnode(this->root, data);
	}
	void Tree_Element_Insert_NonRecursive(DataType data)
	{
		NodeType* current = this->root, * precursor = nullptr;
		while (current)
		{
			precursor = current;
			if (data == current->element)
			{
				std::cout << "Insert failed: Existed" << std::endl;
				return;
			}
			if (data < current->element)
				current = current->left;
			else
				current = current->right;
		}
		NodeType* node = new NodeType(std::to_string(data), data);
		++this->count;
		if (precursor && data < precursor->element)
			precursor->left = node;
		else if (precursor && data > precursor->element)
			precursor->right = node;
		if (!precursor)
			this->root = node;



	}

	//删除二叉搜索子树tree中值为data的节点
	NodeType* Tree_Element_Delete(DataType data)
	{
		return deletenode(this->root, data);
	}

	//定位逻辑后继节点，即右子树的中序首节点
	NodeType* Element_Next(NodeType* node)
	{///不存在抛错
		try
		{
			if (!node->right)
				throw std::exception("No Next Node");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return nullptr;
		}
		node = node->right;
		while (node && node->left)
			node = node->left;
		return node;
	}
	//定位逻辑前驱节点，即左子树的中序末节点
	NodeType* Element_Precursor(NodeType* node)
	{///不存在抛错
		try
		{
			if (!node->left)
				throw std::exception("No Precursor Node");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return nullptr;
		}
		node = node->left;
		while (node && node->right)
			node = node->right;
		return node;
	}

};