#include "../API/Tree_Advanced_B_Tree.h"


B_Node* B_Tree_Create_Node(int order)
{
	B_Node* n = new B_Node;
	n->length = 0;
	n->maxsize = order;
	n->key = new int[order];		///order-1用于存储，多一个元素空间用于预存
	n->index = new B_Node*[order];
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

static void DeleteNode(B_Tree* tree, B_Node* node)
{
	if (node)
	{
		for (int i = 0; i < tree->order; i++)
		{
			if (node->index[i])
			{
				DeleteNode(tree, tree->root->index[i]);
			}
		}
		delete[] node->key;
		delete[] node->index;
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
				DeleteNode(tree, tree->root->index[i]);
	}
}

struct Result
{
	bool tag;		///查找是否成功
	int pos;		///查到的key所在指针索引(node->index[])	失败时为父节点
	B_Node* index;	///查到的key下标索引(node->key[])	失败时为父节点
};
//查找
Result B_Tree_Search(B_Tree* tree, int key)
{
	B_Node* precursor = nullptr;	///父节点索引
	B_Node* current = tree->root;	///当前节点索引
	int pos;		///节点位置
	bool tag{ false };///标记查找状态
	Result result;
	while (current && !tag)
	{///搜索当前节点是否存在目标key
		pos = B_Tree_Node_Locate(current, key);
		if (pos < current->length && current->key[pos] == key)	///查找成功
			tag = true;
		else
		{///查找失败
			precursor = current;
			current = current->index[pos];	///向下层节点找key
		}
	}
	if (tag)
	{///查找成功
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

static void split(B_Tree* tree,B_Node* node, int mid, B_Node* other)
{
	B_Node* sp = B_Tree_Create_Node(tree->order);	///新建同层分裂节点
	other = sp;
	sp->index[0] = node->index[0];
	for (int i = mid, j = 0; i <= node->length; i++, j++)
	{
		sp->key[j] = node->key[i];
		sp->index[j] = node->index[i];
		///清空原位置
		node->key[i] = 0;
		node->index[i] = 0;
	}
	sp->length = tree->order - mid + 1;	///一半分裂出去，非奇数node->maxsize时可能有bug
	sp->parent = node->parent;

	for (int i = 0; i <= sp->length - mid; i++)
	{///将原来的指针索引交给分裂的节点(更新分裂节点的下层parent指针)
		if (sp->index[i])
			sp->index[i]->parent = sp;
	}
	node->length = mid - 1;

}

void B_Tree_Insert(B_Tree* tree, int key)
{
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
	//Insert(tree, res.index, res.pos);
	//(B_Tree * tree, B_Node * node, int pos)
	B_Node* parent = res.index;		///待插节点的父节点
	int pos_parent = res.pos;		///在父节点的指针索引pos位置插入
	B_Node* child = nullptr;		///

	bool loop = false;				///控制while大循环,插入完成后控制退出
	bool root_new = false;			///控制分裂时，是否需要新建上层节点
	//int mid;
	int key_insert = key;			///插入的key

	if (parent)
	{///父节点存在时
		while (!loop && !root_new)
		{///key插入父节点
			{///插入节点
				static int i = parent->length - 1;
				for (i; i>= pos_parent ; i--)
				{
					parent->key[i + 1] = parent->key[i];
					parent->index[i + 2] = parent->index[i + 1];
				}
				parent->index[i + 2] = parent->index[i + 1];
				parent->key[i] = key;
				if (child)
					child->parent = parent;
				parent->length++;
			}
			///插入后判断是否分裂
			if (parent->length < tree->order)
				loop = 1;
			else
			{///节点满，分裂
				int pos_mid = (tree->order + 1) / 2;	///分裂为上层节点
				split(tree, parent, pos_mid, child);
				key_insert = key;	///待插入的key
				key_insert = parent->key[pos_mid];
				if (parent->parent)
				{///上层节点存在时，key插入到上层节点parent中
					parent = parent->parent;
					pos_parent = B_Tree_Node_Locate(parent, key_insert);
				}
				else
					root_new = true;	///需要新建上层节点
			}
		}
	}
	else
	{///父节点不存在时(即空树时)
		B_Node* r = B_Tree_Create_Node(tree->order);///创建上层节点
		tree->root = r;
		r->key[0] = key;
		r->index[0] = nullptr;
		r->index[1] = nullptr;
		r->length++;
	}
	if (root_new)
	{
		B_Node* r = B_Tree_Create_Node(tree->order);///创建上层节点
		tree->root = r;
		r->key[0] = key_insert;
		r->index[0] = parent;
		r->index[1] = child;
		r->length++;
	}
	tree->count++;

}

static void Delete(B_Tree* tree, B_Node* parent, int position)
{
	if (parent->index[position])
	{
		Successor(parent, position);
		Delete(tree, parent, 1);
	}
	else
	{
		RemoveNode(parent, position);
		if (parent->length < (parent->maxsize - 1) / 2);	///阈值可自定义
			//调整B树
	}
}
void B_Tree_Delete(B_Tree* tree, int key)
{
	Result result = B_Tree_Search(tree, key);
	if (result.tag)
	{
		Delete(tree,result.index,result.pos)
		tree->count--;
	}
	else
		std::cout << "key is not exist" << std::endl;
}

void B_Tree_Traverse_Inorder(B_Node* node)
{
	if (node)
	{
		for (int i = 0; i < node->length; i++)
		{
			if (node->index[i])
				B_Tree_Traverse_Inorder(node->index[i]);
				
			std::cout << node->key[i] << ' ';
		}
		B_Tree_Traverse_Inorder(node->index[--node->length]);
	}
}

//定位key在节点中的位置
static int B_Tree_Node_Locate(B_Node* node, int key)
{
	int i = 0;
	while (i < node->length && node->key[i] < key)
		i++;
	return i;
}









