#include "../API/Tree_Advanced_B_Tree.h"


///————————————————————————————————
/// 默认B树节点元素个数最少为 1/2阶数(向下取值)
///		最多为 阶数-1
///————————————————————————————————

B_Node* B_Tree_Create_Node(int order)
{
	B_Node* n = new B_Node;
	n->length = 0;
	n->maxsize = order;
	n->key = new int[order] {};		///order-1个元素用于存储，最后一个元素空间用于预存,如插入时预存分割元素
	n->index = new B_Node * [order] ;
	for (int i = 0; i < order; i++)
		n->index[i] = nullptr;
	n->parent = nullptr;
	return n;
}

void B_Tree_Init(B_Tree* tree, int order)
{
	tree->order = order;
	tree->count = 0;
	tree->root = nullptr;
}

static void Destroy(B_Tree* tree, B_Node* node)
{
	if (node)
	{
		for (int i = 0; i < tree->order; ++i)
		{
			if (node->index[i])
				Destroy(tree, tree->root->index[i]);
		}
		delete[] node->key;
		//delete node->index;
		delete node;
		tree->count--;
	}
}
void B_Tree_Destroy(B_Tree* tree)
{
	if (tree)
	{
		std::cout << "删除B树节点个数:" << tree->count << std::endl;
		if (tree->root)
			for (int i = 0; i < tree->order; i++)
				Destroy(tree, tree->root->index[i]);
	}
}

struct Result
{
	bool tag;		///查找是否成功
	int pos;		///查到的key元素下标索引(parent_node->key[pos])	失败时为NULL
	B_Node* index;	///查到的key所在节点的指针索引	失败时为父节点
};

//定位key在节点中的位置
static int B_Tree_Node_Locate(B_Node* node, int key)
{///返回第一个比key大的元素位置，找其左指针
	int i = 0;
	while (i < node->length && node->key[i] < key)
		++i;
	return i;
}
//查找
Result B_Tree_Search(B_Tree* tree, int key)
{
	B_Node* precursor = nullptr;	///父节点索引
	B_Node* current = tree->root;	///当前节点索引
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



//分割满节点为两个节点，返回待插入的key
static std::pair<int,B_Node*> split(B_Tree* tree,B_Node* node, int mid)
{
	/// <summary>
	/// 以mid为下标，将mid后所有元素移动到新节点
	/// 原有位置置为NULL
	/// 重置分割位置元素值，并返回该元素值
	/// </summary>
	/// <param name="tree"></param>
	/// <param name="node"></param>
	/// <param name="mid"></param>
	/// <param name="other"></param>
	/// <returns></returns>
	
	B_Node* sp = B_Tree_Create_Node(tree->order);	///新建同层分裂节点

	//int guard = node->length == node->maxsize ? node->length+1 : node->length;
	for (int i = mid+1, j = 0; i < node->length; i++, j++)
	{///将分割元素的后面所有元素移动到新节点
		sp->key[j] = node->key[i];
		sp->index[j] = node->index[i];
		///清空原位置
		node->key[i] = NULL;
		node->index[i] = NULL;
	}
	sp->length = tree->order - mid - 1;	///一半分裂出去，非奇数node->maxsize时可能有bug
	if (node->length == node->maxsize)
	{///补丁：用于添加到满父节点后，最后一个索引指针不移动给新节点
		sp->index[sp->length] = node->index[node->length];
		node->index[node->length] = NULL;
	}
	sp->parent = node->parent;

	for (int i = 0; i <= sp->length; i++)
	{///将原来的指针索引交给分裂的节点(更新分裂节点的下层parent指针)
		if (sp->index[i])
			sp->index[i]->parent = sp;
	}
	node->length = mid;
	
	///将分割元素返回
	int element = node->key[mid];
	node->key[mid] = NULL;

	return std::pair<int, B_Node*>(element,sp);;
}

void B_Tree_Insert(B_Tree* tree, int key)
{
	/// 定位待插入节点及下标位置
	Result res = B_Tree_Search(tree, key);
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

	B_Node* node = res.index;		///元素插入的节点，此处因为Result搜索失败，所以返回查找节点的父节点声明为parent(即插入节点)
	int pos_node = res.pos;			///元素插入的节点的下标索引pos位置插入元素key(pos=第一个大元素的下标位置)
	B_Node* child = nullptr;		///分裂的新节点

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
					for (i; i>= pos_node; --i)
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
			if (node->length < tree->order)
				loop = false;
			else
			{///节点满，分裂
				int pos_mid = (tree->order) / 2;	///分裂为上层节点
				//TODO BUG
				std::pair<int, B_Node*> pair;
				///分割满节点为两个节点，返回待插入的key
				pair= split(tree, node, pos_mid);
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
		B_Node* r = B_Tree_Create_Node(tree->order);///创建上层节点
		tree->root = r;
		r->key[0] = key;
		++r->length;
	}
	if (root_new)
	{
		B_Node* root = B_Tree_Create_Node(tree->order);///创建上层节点
		tree->root = root;
		root->key[0] = key_insert;
		root->index[0] = node;
		root->index[1] = child;
		node->parent = root;
		child->parent = root;
		root->length++;
	}
	tree->count++;

}

static void RestoreBTree(B_Tree* tree, B_Node* parent)
{

}
static void RemoveNode(B_Node* parent, int position)
{

}
static void Successor(B_Node* parent, int position)
{
	B_Node* leaf = parent;
	if (leaf)
		return;
	leaf = leaf->index[position];
	while (leaf->index[0])
		leaf = leaf->index[0];
	parent->key[position] = leaf->key[0];
	parent = leaf;
}
static void Delete(B_Tree* tree, B_Node* parent, int position)
{
	if (parent->index[position])
	{///删除非叶节点
		Successor(parent, position);	///用逻辑后继节点代替(父节点元素代替，父节点用右子树第一个代替)
		Delete(tree, parent, 1);		///删除逻辑后继(父节点元素)
	}
	else
	{///删除叶节点
		RemoveNode(parent, position);	///直接删除叶节点
		if (parent->length < (parent->maxsize - 1) / 2)	///阈值可自定义
			RestoreBTree(tree, parent);///调整B树
	}
}
void B_Tree_Delete(B_Tree* tree, int key)
{
	Result result = B_Tree_Search(tree, key);
	if (result.tag)
	{
		Delete(tree, result.index, result.pos);
		tree->count--;
	}
	else
		std::cout << "key is not exist" << std::endl;
}

void B_Tree_Traverse_Inorder(B_Node* node)
{
	if (node)
	{
		for (int i = 0; i < node->length; ++i)
		{
			if (node->index[i])	///感觉多余
				B_Tree_Traverse_Inorder(node->index[i]);
		///——————————————————————————————————递归分割
			std::cout << node->key[i] << ' ';
		}
		B_Tree_Traverse_Inorder(node->index[node->length]);
	}
}










