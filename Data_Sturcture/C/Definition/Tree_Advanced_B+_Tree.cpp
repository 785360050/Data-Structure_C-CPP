#include "../API/Tree_Advanced_B+_Tree.h"

#include <iostream>
#include <string>

static bool Element_Greater(int a, int b)
{
	return a - b > 0;
}


BPlus_Node* BPlus_Node_Create_Leaf(int m)
{
	BPlus_Node* node = new BPlus_Node;
	if (node == nullptr)
		return nullptr;

	node->parent = nullptr;
	node->next = nullptr;
	node->count = 0;
	node->keys = new int[m + 1] {};
	node->data = new int[m + 1] {};
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
	node->keys = new int[m + 1] {};
	node->data = nullptr;//索引节点不存数据
	if (node->keys == nullptr)
	{
		delete node->keys;
		delete node->data;
		delete node;
		return nullptr;
	}
	node->child = new BPlus_Node * [m + 2] {};///为什么要+2
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

#include <queue>
void BPlus_Tree_Destroy(BPlus_Tree* tree)
{///层次遍历释放节点
	std::queue<BPlus_Node*> queue;
	int i = 0;
	queue.push(tree->root);
	while (!queue.empty())
	{
		auto node = queue.front();
		if (node->child)
			for (int i = 0; i <= node->count; ++i)
				queue.push(node->child[i]);
		queue.pop();
		delete node;
		++i;
	}
	std::cout << "Node Deleted Count: " << i << std::endl;

}



////二分查找 找到数组中指定的key的位置 如果存在返回1 否则返回0
////如果找到索引为该值的位置 否则返回右邻的值的位置(child的位置)
//static bool binary_search(int* keys, int key, int left, int right, int* index)
//{
//	int mid;
//	while (left <= right)
//	{
//		mid = (left + right) / 2;
//		if (keys[mid] == key)
//		{
//			*index = mid;
//			return true;
//		}
//		if (Element_Greater(keys[mid], key))
//			right = mid - 1;
//		else
//			left = mid + 1;
//	}
//	*index = left;
//	return false;
//}

///返回找目标key时下一个路径孩子节点
static BPlus_Node* Locate_Child(BPlus_Node* node, int key)
{
	if (!node)
		throw std::runtime_error("Node Unexists");
	for (int i = 0; i < node->count; i++)
	{
		if (node->keys[i] < key)
			continue;
		if (key < node->keys[i])
			return node->child[i];
		else
			return node->child[i + 1];
	}
	return node->child[node->count];
}
///返回key在叶子节点插入的位置索引，已经存在时返回-1
static int Locate_Key(BPlus_Node* node, int key)
{
	if (!node)
		throw std::runtime_error("Node Unexists");

	for (int i = 0; i < node->count; ++i)
	{
		if (node->keys[i] < key)
			continue;
		if (key == node->keys[i])
			return -1;
		if (key < node->keys[i])
			return i - 1;
	}
	return 0;
}
///返回key在node中的下标，不存在返回-1
static int Locate_Key_Delete(BPlus_Node* node, int key)
{
	if (!node)
		throw std::runtime_error("Node Unexists");

	for (int i = 0; i < node->count; ++i)
	{
		if (key == node->keys[i])
			return i;
	}
	return -1;
}

//元素的插入以及分裂操作
static void _BPlus_Tree_Insert(BPlus_Tree* tree, BPlus_Node* node, int key, int value)
{
	BPlus_Node* parent;
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
	while (node->count >= tree->max)
	{
		BPlus_Node* sibling;
		// 拷贝数据
		mid = node->count / 2;//中间位置索引
		temp = node->keys[mid];//中间元素
		/*分裂结点*/
		if (!node->child)// 叶子结点分裂
		{
			sibling = BPlus_Node_Create_Leaf(tree->max);
			sibling->count = node->count - mid;

			for (int i = 0; i < sibling->count; ++i)
			{//拷贝元素和数据
				sibling->keys[i] = node->keys[mid + i];
				sibling->data[i] = node->data[mid + i];
				node->keys[mid + i] = node->data[mid + i] = 0;//置空
			}

			//插入叶子的链式节点
			sibling->next = node->next;
			node->next = sibling;
		}
		else// 索引结点分裂
		{///注意：索引节点的分裂会把分裂节点向上移动，而不是像子节点一样存右子树的第一个元素
			sibling = BPlus_Node_Create_Branch(tree->max);
			sibling->count = node->count - mid - 1;//分裂元素不给兄弟节点

			/// 将分割出去的孩子转交给新分裂的兄弟节点
			for (int i = 0; i < sibling->count; ++i)
			{//拷贝元素和数据
				sibling->keys[i] = node->keys[mid + i + 1];
				sibling->child[i] = node->child[mid + i + 1];
				sibling->child[i]->parent = sibling;

				node->keys[mid + i + 1] = 0;//置空
				node->child[mid + i + 1] = nullptr;
			}
			//sibling->child[sibling->count] = node->child[node->count];
			sibling->child[sibling->count] = node->child[node->count];
			sibling->child[sibling->count]->parent = sibling;

		}
		node->count = mid;

		///被分裂的元素插入父节点
		parent = node->parent;
		if (!parent)//父节点不存在，生成新索引节点(该索引节点为新根节点)
		{
			parent = BPlus_Node_Create_Branch(tree->max);
			if (!parent)
				throw std::runtime_error("Parent Create Failed");
			parent->child[0] = node;
			node->parent = parent;
			tree->root = parent;
		}

		///索引元素插入父节点

		//先一边往后移动元素，一边定位插入位置
		for (i = parent->count; i > 0 && Element_Greater(parent->keys[i - 1], temp); i--)
		{
			parent->keys[i] = parent->keys[i - 1];
			parent->child[i + 1] = parent->child[i];
		}

		parent->keys[i] = temp;
		if (parent->child[0]->child)//若子节点为索引节点
			node->keys[mid] = 0;
		parent->child[i + 1] = sibling;
		parent->count++;

		sibling->parent = parent;

		// 向上继续判断是否父节点需要分裂
		node = parent;
	}
}


void BPlus_Tree_Insert(BPlus_Tree* tree, int key, int value)
{
	BPlus_Node* node;
	int index;

	///空树创建根(叶子)节点
	if (!tree->root)
	{
		node = BPlus_Node_Create_Leaf(tree->max);
		if (node == nullptr)
			throw std::exception("Node Create Failed");
		tree->root = node;
	}

	node = tree->root;

	///————————————————————————————————————————————————————————
	/// 定位插入元素的位置
	/// 先找到插入的叶子节点，再再叶子节点中找插入位置索引
	///————————————————————————————————————————————————————————

	while (node->child)
	{
		node = Locate_Child(node, key);
		if (!node)
			throw std::runtime_error("Node Unexists");
	}

	index = Locate_Key(node, key);
	if (index == -1)
		return;//已经存在元素了


	///找到插入位置后插入元素
	_BPlus_Tree_Insert(tree, node, key, value);
}


//叶子结点的左旋转 把右节点的第一个值移到左节点
void _bplus_leaf_left_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
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

	//覆盖完成后才能设置父节点值，否则是原来的值，可能变成左兄弟的末尾元素
	node->keys[index] = right->keys[0];

	right->count--;

}

//内部结点的左旋转 把右节点的第一个值移到父节点 父节点对应的值移到左节点
void _bplus_internal_left_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];

	left->keys[left->count] = node->keys[index];
	left->child[left->count + 1] = right->child[0];
	left->child[left->count + 1]->parent = left;
	left->count++;

	node->keys[index] = right->keys[0];

	// 对右节点进行移位
	for (int i = 0; i < right->count - 1; i++)
		right->keys[i] = right->keys[i + 1];

	for (int i = 0; i < right->count; i++)
		right->child[i] = right->child[i + 1];

	right->count--;
}

//合并结点元素的左右两个子节点,index左孩子的索引值
void _BPlus_Node_merge(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];
	if (!left->child)///合并叶子节点
	{//合并到左子节点

		for (int i = 0; i < right->count; ++i)
		{
			left->keys[left->count + i] = right->keys[i];
			left->data[left->count + i] = right->data[i];
		}

		left->count += right->count;

		///修改索引元素
		for (int i = index; i < node->count - 1 ; i++)
			node->keys[i] = node->keys[i + 1];
		node->keys[node->count - 1] = 0;
		//(合并到左节点不应该删右边的索引吗？)
		//删除左节点的索引(直接覆盖) (int i = index是否+1有bug)
		for (int i = index + 1; i <= node->count-1; i++)
			node->child[i] = node->child[i + 1];
		node->child[node->count] = nullptr;
		node->count--;

		left->next = right->next;
	}
	else///合并索引节点
	{
		//从父节点把分割元素移下来(这里不需要考虑孩子指针移动)
		left->keys[left->count] = node->keys[index];
		if (node->count == 1)//归还被分割索引节点为叶子节点的父节点指向
			right->child[0]->parent = left;
		left->count++;


		//把右边元素合并到左边
		for (int i = 0; i < right->count; ++i)
		{
			left->keys[left->count + i] = right->keys[i];
			right->keys[i] = 0;
		}

		for (int i = 0; i <= right->count; ++i)
		{
			left->child[left->count + i] = right->child[i];
			right->child[i]->parent = left;
			right->child[i] = nullptr;
		}

		left->count += right->count;
		right->count = 0;

		///修改父索引节点
		//删除移动下来的key
		for (int i = index; i < node->count - 1; i++)
			node->keys[i] = node->keys[i + 1];
		node->keys[node->count - 1] = 0;

		//合并索引后，删除夫节点的孩子索引(直接覆盖，每次覆盖右孩子)
		for (int i = index + 1; i <= node->count; i++)
			node->child[i] = node->child[i + 1];
		node->child[node->count] = nullptr;
		node->count--;

		left->next = right->next;
	}

	/*修改父节点*/


	/*释放右节点*/
	free(right->keys);
	free(right->data);
	free(right->child);
	free(right);
}

//叶子结点的右旋转
void _bplus_leaf_right_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];

	for (int i = right->count; i > 0; i--)
	{//向后移动，留出插入位置
		right->keys[i] = right->keys[i - 1];
		right->data[i] = right->data[i - 1];
	}
	right->count++;
	right->keys[0] = left->keys[left->count - 1];
	right->data[0] = left->data[left->count - 1];

	left->count--;
	//node->keys[index] = right->keys[0];
	node->keys[index] = right->keys[0];///parent索引节点改为移动的前一个元素
}

//内部结点的右旋转 左节点的最后一个值到父节点 父节点对应的值到右节点
void _bplus_internal_right_rotate(BPlus_Node* node, int index)
{
	BPlus_Node* left, * right;
	left = node->child[index];
	right = node->child[index + 1];
	for (int i = right->count; i > 0; i--)
		right->keys[i] = right->keys[i - 1];

	right->keys[0] = node->keys[index];
	for (int i = right->count + 1; i > 0; i--)
		right->child[i] = right->child[i - 1];
	right->child[0] = left->child[left->count];
	right->child[0]->parent = right;
	right->count++;

	node->keys[index] = left->keys[left->count - 1];
	left->count--;
}


///删除叶子节点node上的第index个元素
static void _BPlus_Tree_delete(BPlus_Tree* tree, BPlus_Node* node, int index)
{
	BPlus_Node* parent, * sibling;



	///若叶子节点删除第一个元素，则修改对应索引节点的索引值
	if (index == 0 && !node->child && node->parent)
	{
		BPlus_Node* node_index=node->parent;
		int key_target = node->keys[index];
		int i = Locate_Key_Delete(node_index, key_target);
		while (i>=node_index->count||i==-1)
		{//一直向上层找key所在的节点
			node_index = node_index->parent;
			i= Locate_Key_Delete(node_index, key_target);
		}
		//找到后覆盖数据
		node_index->keys[i] = node->keys[1];
		
	}

	///删除叶子结点的指定的值
	//从后往前覆盖
	for (int i = index; i < node->count - 1; i++)
	{
		node->keys[i] = node->keys[i + 1];
		node->data[i] = node->data[i + 1];
	}
	node->count--;
	node->keys[node->count] = 0;

	parent = node->parent;
	///一层一层向上维护索引节点元素数量
	while (node->count < tree->min && parent)
	{
		///定位结点在父节点中的索引位置
		for (index = 0; index <= parent->count && parent->child[index] != node; index++)
			;
		if (index > parent->count)// 在他的父节点中没找到这个孩子
			throw std::logic_error("No Matching Node but Element Delete Found");
		if (index == 0)///没有左兄弟 只有右兄弟
		{

			sibling = parent->child[1];
			if (sibling->count > tree->min)///兄弟有富余元素，将富余元素移过来(最小元素)
			{
				// 迁移数据
				if (!node->child)
					// 叶子结点的迁移
					_bplus_leaf_left_rotate(parent, 0);
				else
					_bplus_internal_left_rotate(parent, 0);
			}
			else///兄弟俩节点都没有富余元素时，合并兄弟为一个
				_BPlus_Node_merge(parent, 0);

		}
		else///只有左兄弟、或两边都有兄弟，向左边兄弟拿元素
		{
			sibling = parent->child[index - 1];
			if (sibling->count > tree->min)
			{
				// 从左兄弟迁移数据
				if (!node->child)
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


		

	///如果根节点的两个孩子合并，将合并后的孩子节点作为新的根节点
	if (tree->root->count == 0 && tree->root->child != nullptr)
	{
		node = tree->root;
		tree->root = node->child[0];

		///删除头节点后清空孩子的父节点
		node->child[0]->parent = nullptr;
		free(node->keys);
		free(node->data);
		free(node->child);
		free(node);
	}
}


void BPlus_Tree_Delete(BPlus_Tree* tree, int key)
{
	BPlus_Node* node = tree->root;
	int index;

	///先查索引节点找到叶子，再找目标元素在节点中的index
	while (node->child)
	{
		node = Locate_Child(node, key);
		if (!node)
			throw std::runtime_error("Node Unexists");
	}

	index = Locate_Key_Delete(node, key);
	if (index == -1)
		return;//不存在该元素

	///找到删除位置后删除目标元素
	_BPlus_Tree_delete(tree, node, index);

	return;
}



static void Node_Print(BPlus_Node* node)
{
	std::vector<int> temp;
	std::cout << '{';
	///深度遍历输出元素
	for (int i = 0; i < node->count; i++)
	{
		if (i != 0)
			std::cout << ',';
		std::cout << node->keys[i];
		temp.push_back(node->keys[i]);
	}
	std::cout << '}';

	///Details to Debug
//	std::cout << '[';
//	if (!node->child)
//	{
//		std::cout << "Leaf";
//		goto END;
//	}
//	///深度遍历输出元素
//	for (int i = 0; i < node->count; i++)
//	{
//		//if (!node->child)
//		//	break;
//		if (i != 0)
//			std::cout << ',';
//		std::cout << node->child[i]->keys[0];
//		
//		//if (i == 0)
//		//	continue;
//		//if (temp[i-1] != node->child[i]->keys[0])
//		//	throw std::logic_error("Errors Occured");
//	}
//	std::cout << (node->child[node->count] ? "," + std::to_string(node->child[node->count]->keys[0]) : "");
//END:
//	std::cout << ']';
//	std::cout << '('<< (!node->parent ? "Root)" : std::to_string(node->parent->keys[0]) + ")");

	if (node->child)
		return;
	std::cout << '<';
	///深度遍历输出元素
	for (int i = 0; i < node->count; i++)
	{
		if (i != 0)
			std::cout << ',';
		std::cout << node->data[i];
			
	}
	std::cout << '>';
}

static void Traver(BPlus_Node* node)
{
	std::cout << '{';
	///深度遍历输出元素
	for (int i = 0; i < node->count; i++)
	{
		if (i != 0)
			std::cout << ',';
		std::cout << node->keys[i];
	}
	std::cout << '}';
}

#include <vector>
//static void BPlus_Level_Show(BPlus_Node* node, int h)
//{
//	if (node == nullptr)
//		return;
//	if (node->child != nullptr)
//		;	//BPlus_Node_Show(node->child[0], h + 1);
//
//	auto node_current = node;
//	while (node_current->child)
//		node_current = node_current->child[0];
//	while (node_current)
//	{
//		BPlus_Node_printfnode(node_current);
//		std::cout << (node_current->next ? "--->" : "\n");
//		node_current = node_current->next;
//	}
//
//
//
//}
static void BPlus_Level_Show(BPlus_Node* node, int h)
{
	if (node == nullptr)
		return;
	if (node->child != nullptr)
		;	//BPlus_Node_Show(node->child[0], h + 1);

	std::vector<std::vector<BPlus_Node*>> buffer;

	int level = 1;
	buffer.push_back({ node });
	//for (int i = 0; i < node->count; ++i)
	//	level


}


std::vector<std::vector<BPlus_Node*>> buffer;
int level = 0;
///回溯实现遍历生成所有树中的节点信息，存入数组
static void BackTrace_Traverse(std::vector<BPlus_Node*>*& buffer, BPlus_Node* node, int level)
{
	if (!node)
		return;

	buffer[level].push_back(node);
	if (!node->child)
		return;

	for (int i = 0; i <= node->count; ++i)
	{//遍历所有孩子节点，加入对应层的数组中
		level++;
		//if(i==node->count && !node->child[i])


		BackTrace_Traverse(buffer, node->child[i], level);
		level--;
	}
}

void Print_Tree(std::vector<BPlus_Node*>*& buffer, int level)
{

	///以行为单位显示每一层的节点
	for (int i = 0; i < level - 1; ++i)
	{
		///索引节点稍微居中一些显示
		for (int j = 0; j < (level - i); ++j)
			std::cout << '\t';

		for (const auto& node : buffer[i])//索引节点格式化
		{
			Node_Print(node);
			std::cout << '\t';
		}
		std::cout << std::endl;
	}

	///显示最底层的叶子节点
	auto node = buffer[level - 1][0];
	while (node)
	{
		Node_Print(node);
		if (node->next)
		{
			std::cout << "->";
			node = node->next;
		}
		else
		{
			std::cout << "\n";
			return;
		}
	}


}

int BPlus_Tree_Search(BPlus_Tree* tree, int key)
{
	if (!tree)
		throw std::exception("tree is nullptr");

	auto node = tree->root;
	while (node->child)
	{
		node = Locate_Child(node, key);
		if (!node)
			throw std::runtime_error("Node Unexists");
	}

	//这个函数命名不友好，晚点改一下
	int index = Locate_Key_Delete(node, key);
	if (index != -1)
		return node->data[index];
	else
		return -1;
}

void BPlus_Tree_Show(BPlus_Tree* tree)
{
	//BPlus_Level_Show(tree->root, 0);

	auto node = tree->root;
	int level = 1;
	while (node->child)
	{//所有叶子节点深度相同
		++level;
		node = node->child[0];
	}

	std::vector<BPlus_Node*>* buffer = new std::vector<BPlus_Node*>[level];
	BackTrace_Traverse(buffer, tree->root, 0);

	std::cout << "Tree=======================================" << std::endl;
	Print_Tree(buffer, level);
	std::cout << "===========================================" << std::endl;
	delete[] buffer;
}
