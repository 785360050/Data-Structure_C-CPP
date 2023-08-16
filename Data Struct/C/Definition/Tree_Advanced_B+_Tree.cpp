#include "../API/Tree_Advanced_B+_Tree.h"

#include <iostream>

static bool Element_Greater(int a,int b)
{return a-b>0;}


BPlus_Node* BPlus_Node_Create_Leaf(int m)
{
	BPlus_Node* node = new BPlus_Node;
	if (node == nullptr)
		return nullptr;

	node->parent = nullptr;
	node->next = nullptr;
	node->count = 0;
	node->keys = new int[m + 1];
	node->data = new int[m + 1];
	if (node->keys == nullptr || node->data == nullptr)
	{
		delete node->keys;
		delete node->data;
		delete node;
		return nullptr;
	}
	node->child = nullptr;
	return node;
}

BPlus_Node* BPlus_Node_Create_Branch(int m)
{
	BPlus_Node* node = new BPlus_Node;
	if (node == nullptr)
		return nullptr;

	node->parent = nullptr;
	node->next = nullptr;
	node->count = 0;
	node->keys = new int[m + 1];
	node->data = nullptr;
	if (node->keys == nullptr || node->data == nullptr)
	{
		delete node->keys;
		delete node->data;
		delete node;
		return nullptr;
	}
	node->child = new BPlus_Node*[m + 2];
	return node;
}


BPlus_Tree* BPlus_Tree_Init(int orders)
{
	BPlus_Tree* tree = new BPlus_Tree;
	if (!tree)
		return nullptr;
	tree->root = nullptr;
	tree->max = orders;
	tree->min = orders / 2;
	return tree;
}



//二分查找 找到数组中指定的key的位置 如果存在返回1 否则返回0
//如果找到索引为该值的位置 否则返回右邻的值的位置(child的位置)
static int binary_search(int* keys, int key, int left, int right, int* index)
{
	int mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (Element_Greater(keys[mid], key) )
			right = mid - 1;
		else if (!Element_Greater(keys[mid], key))
			left = mid + 1;
		else
		{
			*index = mid;
			return 1;
		}
	}
	*index = left;
	return 0;
}

//元素的插入以及分裂操作
static void _BPlus_Tree_Insert(BPlus_Tree* tree, BPlus_Node* node, int key, int value)
{
	BPlus_Node* parent,* node2;
	int mid;
	int temp;
	int i;

	///先插入到叶子节点
	//向后移动元素
	for (i = node->count; i > 0 && Element_Greater(node->keys[i - 1], key); i--)
	{
		node->keys[i] = node->keys[i - 1];
		node->data[i] = node->data[i - 1];
	}
	//插入新元素
	node->keys[i] = key;
	node->data[i] = value;
	node->count++;


	///节点过载时分裂
	while (node->count > tree->max)
	{
		/*分裂结点*/
		if (node->child == nullptr)// 叶子结点分裂
			node2 = BPlus_Node_Create_Leaf(tree->max);
		else// 内部结点分裂
			node2 = BPlus_Node_Create_Branch(tree->max);

		if (!node2)
			throw std::exception("Node is nullptr");
		// 拷贝数据
		mid = node->count / 2;
		temp = node->keys[mid];
		if (node->child == nullptr)
		{
			node2->count = node->count - mid;
			memcpy(node2->keys, node->keys + mid, sizeof(int) * (node2->count));
			memcpy(node2->data, node->data + mid, sizeof(int) * (node2->count));
			node2->next = node->next;
			node->next = node2;
		}
		else
		{

			node2->count = node->count - mid - 1;

			memcpy(node2->keys, node->keys + mid + 1, sizeof(int) * (node2->count));
			memcpy(node2->child, node->child + mid + 1, sizeof(BPlus_Node*) * (node->count - mid));

			// 重新设置父指针
			for (int i = 0; i <= node2->count; i++)
				node2->child[i]->parent = node2;
		}

		node->count = mid;

		/*插入父节点*/
		parent = node->parent;
		if (parent == nullptr)
		{
			// 生成一个新的根节点
			parent = BPlus_Node_Create_Branch(tree->max);
			if (parent == nullptr)
				return ;
			parent->child[0] = node;
			node->parent = parent;
			tree->root = parent;
		}

		/*增加数据 右子树*/
		for (i = parent->count; i > 0 && Element_Greater(parent->keys[i - 1], temp) ; i--)
		{
			parent->keys[i] = parent->keys[i - 1];
			parent->child[i + 1] = parent->child[i];
		}

		parent->keys[i] = temp;
		parent->child[i + 1] = node2;
		parent->count++;

		node2->parent = parent;

		// 回溯 向上继续判断
		node = parent;
	}
}


void BPlus_Tree_Insert(BPlus_Tree* tree, int key, int value)
{
	BPlus_Node* node;
	int ret, index;

	///空树创建叶子节点
	if (tree->root == nullptr)
	{
		node = BPlus_Node_Create_Leaf(tree->max);
		if (node == nullptr)
			throw std::exception("Node Create Failed");
		tree->root = node;
	}

	node = tree->root;
	/// 定位插入元素的位置
	/// 先找到插入的叶子节点
	while (node->child != nullptr)
	{
		ret = binary_search(node->keys, key, 0, node->count - 1, &index);
		if (ret == 1)
			index++;
		node = node->child[index];
	}

	///定位叶子节点中元素的插入位置(数组位置)
	ret = binary_search(node->keys, key, 0, node->count - 1, &index);
	if (ret == 1)
		// 这个结点已经存在了
		throw std::exception("Element Already Existed");
	_BPlus_Tree_Insert(tree, node, key, value);
}


//叶子结点的左旋转 把右节点的第一个值移到左节点
void _bplus_leaf_left_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left,* right;
	left = node->child[index];
	right = node->child[index + 1];
	left->keys[left->count] = right->keys[0];
	left->data[left->count] = right->data[0];
	left->count++;

	// 对右节点进行移位
	for (int i = 0; i < right->count - 1; i++)
	{
		right->keys[i] = right->keys[i + 1];
		right->data[i] = right->data[i + 1];
	}

	right->count--;

	node->keys[index] = right->keys[0];
}

//内部结点的左旋转 把右节点的第一个值移到父节点 父节点对应的值移到左节点
void _bplus_internal_left_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];

	left->keys[left->count] = node->keys[index];
	left->child[left->count + 1] = right->child[0];
	left->count++;

	node->keys[index] = right->keys[0];

	// 对右节点进行移位
	for (int i = 0; i < right->count - 1; i++)
		right->keys[i] = right->keys[i + 1];

	for (int i = 0; i < right->count; i++)
		right->child[i] = right->child[i + 1];

	right->count--;
}

//合并结点元素的左右两个子节点
void _BPlus_Node_merge(BPlus_Node* node, int index)
{
	BPlus_Node* left,* right;
	left = node->child[index];
	right = node->child[index + 1];
	if (left->child != nullptr)
	{
		/*修改左子节点*/
		left->keys[left->count] = node->keys[index];
		memcpy(left->keys + left->count + 1, right->keys, sizeof(int) * (right->count));

		for (int i = 0; i <= right->count; i++)
		{
			right->child[i]->parent = left;
			left->child[left->count + i + 1] = right->child[i];
		}

		left->count = left->count + right->count + 1;
	}
	else
	{
		memcpy(left->keys + left->count, right->keys, sizeof(int) * (right->count));
		memcpy(left->data + left->count, right->data, sizeof(int) * (right->count));

		left->count = left->count + right->count;
	}

	/*修改父节点*/
	for (int i = index; i < node->count - 1; i++)
		node->keys[i] = node->keys[i + 1];

	for (int i = index + 1; i < node->count; i++)
		node->child[i] = node->child[i + 1];
	node->count--;

	/*释放右节点*/
	free(right->keys);
	free(right->data);
	free(right->child);
	free(right);
}

//叶子结点的右旋转
void _bplus_leaf_right_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left,* right;
	left = node->child[index];
	right = node->child[index + 1];

	for (int i = right->count; i > 0; i--)
	{
		right->keys[i] = right->keys[i - 1];
		right->data[i] = right->data[i - 1];
	}
	right->count++;
	right->keys[0] = left->keys[left->count - 1];
	right->data[0] = left->data[left->count - 1];

	left->count--;
	node->keys[index] = right->keys[0];
}

//内部结点的右旋转 左节点的最后一个值到父节点 父节点对应的值到右节点
void _bplus_internal_right_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left,* right;
	left = node->child[index];
	right = node->child[index + 1];
	for (int i = right->count; i > 0; i--)
	{
		right->keys[i] = right->keys[i - 1];
	}
	right->keys[0] = node->keys[index];
	for (int i = right->count + 1; i > 0; i--)
	{
		right->child[i] = right->child[i - 1];
	}
	right->child[0] = left->child[left->count];
	right->count++;

	node->keys[index] = left->keys[left->count - 1];
	left->count--;
}


///删除叶子节点node上的第index个元素
static void _BPlus_Tree_delete(BPlus_Tree* tree, BPlus_Node* node, int index)
{
	BPlus_Node* parent, *sibling;
	
	///先删除叶子结点的指定的值

	//从后往前覆盖
	for (int i = index; i < node->count - 1; i++)
	{
		node->keys[i] = node->keys[i + 1];
		node->data[i] = node->data[i + 1];
	}
	node->count--;

	parent = node->parent;
	while (node->count < tree->min && parent != nullptr)
	{
		/*寻找到当前结点在父节点当中的位置*/
		for (index = 0; index <= parent->count && parent->child[index] != node; index++)
			;
		if (index > parent->count)// 在他的父节点中没找到这个孩子
			return;
		if (index == 0)
		{
			// 如果是第一个结点  没有左兄弟 只有右兄弟
			sibling = parent->child[1];
			if (sibling->count > tree->min)
			{
				// 迁移数据
				if (node->child == nullptr)
					// 叶子结点的迁移
					_bplus_leaf_left_rotate(parent, 0);
				else
					_bplus_internal_left_rotate(parent, 0);
			}
			else
				/*合并兄弟*/
				_BPlus_Node_merge(parent, 0);
		}
		else
		{
			/*
			如果结点是父节中的第index个子节点，兄弟是第index - 1
			中间的分割元素是父节点中的第index - 1个元素
			*/
			sibling = parent->child[index - 1];
			if (sibling->count > tree->min)
			{
				// 从左兄弟迁移数据
				if (node->child == nullptr)
					// 叶子结点的右旋转
					_bplus_leaf_right_rotate(parent, index - 1);
				else
					// 内部结点的右旋转
					_bplus_internal_right_rotate(parent, index - 1);
			}
			else///合并兄弟
				_BPlus_Node_merge(parent, index - 1);
		}

		node = parent;
		parent = node->parent;
	}

	if (tree->root->count == 0 && tree->root->child != nullptr)
	{
		node = tree->root;
		tree->root = node->child[0];
		free(node->keys);
		free(node->data);
		free(node->child);
		free(node);
	}
}


void BPlus_Tree_Delete(BPlus_Tree* tree, int key)
{
	BPlus_Node* node = tree->root;
	int ret = 0, index;
	/*先查找到叶子*/
	while (node->child != nullptr)
	{
		ret = binary_search(node->keys, key, 0, node->count - 1, &index);
		if (ret == 1)
			index++;
		node = node->child[index];
	}
	ret = binary_search(node->keys, key, 0, node->count - 1, &index);
	if (ret == 0)
		return;

	_BPlus_Tree_delete(tree, node, index);

	return;
}




static void BPlus_Node_printfnode(int* key, int h)
{
	for (int i = 0; i < h; i++)
		std::cout << "   ";
	if (key == nullptr)
		std::cout << "\n";
	else
		std::cout << *key << std::endl;
}

static void BPlus_Node_Show(BPlus_Node* node, int h)
{
	if (node == nullptr)
		return;
	if (node->child != nullptr)
		BPlus_Node_Show(node->child[0], h + 1);
	for (int i = 0; i < node->count; i++)
	{
		BPlus_Node_printfnode(&node->keys[i], h);
		if (node->child != nullptr)
			BPlus_Node_Show(node->child[i + 1], h + 1);
	}
}

void BPlus_Tree_Show(BPlus_Tree* tree)
{
	BPlus_Node_Show(tree->root, 0);
}
