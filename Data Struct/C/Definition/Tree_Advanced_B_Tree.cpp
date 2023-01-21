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
				Destroy(tree, node->index[i]);
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
{///返回元素值为key的下标位置，失败时返回第一个比key大的元素位置，找其左指针
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

void RestoreBTree(B_Tree* tree, B_Node* node);
static void BorrowFromBrothers(B_Node* node, B_Node* brother_left, B_Node* brother_right, B_Node* parent, int position)
{
	if (brother_left && brother_left->length > node->maxsize / 2)
	{///从左兄弟借元素
		for (int i = node->length; i >= 0; --i)
		{///后移元素，留出第一个位置
			node->key[i] = node->key[i - 1];
			node->index[i] = node->index[i - 1];
		}
		node->index[0] = brother_left->index[brother_left->length];
		if (node->index[0])
			node->index[0]->parent = node;

		brother_left->index[brother_left->length] = nullptr;
		node->key[0] = parent->key[position];
		parent->key[position] = brother_left->key[brother_left->length];
		--brother_left->length;
		++node->length;
	}
	else if(brother_right && brother_right->length > node->maxsize / 2)
	{///从右兄弟借元素
		///先把父元素移下来
		node->key[node->length] = parent->key[position];
		//node->index[node->length] = parent->index[0];///？？？
		
		if (node->index[node->length])
			node->index[node->length]->parent = node;
		++node->length;
		///再把右兄弟的第一个元素移上来(逻辑后继)
		parent->key[position] = brother_right->key[0];
		for (int i = 0; i <brother_right->length; ++i)
		{///右兄弟被抽走一个元素，前移一格
			brother_right->key[i] = brother_right->key[i + 1];
			brother_right->index[i] = brother_right->index[i + 1];
		}

		brother_right->index[brother_right->length+1] = nullptr;
		--brother_right->length;
	}
}
static void Merger_Brother_Left(B_Tree* tree, B_Node* brother_left, B_Node* parent, B_Node* node, int position)
{
	// 从父节点移下分割元素
	brother_left->key[brother_left->length] = parent->key[position];   
	brother_left->index[brother_left->length + 1] = node->index[0];
	if (brother_left->index[brother_left->length + 1]) 
		// 给左兄弟的节点，当此结点存在时需要把其父亲指向左节点
		brother_left->index[brother_left->length + 1]->parent = brother_left;
	++brother_left->length;      // 左兄弟关键字加1
	for (int i = 0; i < node->length; ++i) 
	{/// 把本节点的元素和子树指针赋给左兄弟
		brother_left->key[brother_left->length + i] = node->key[i];
		brother_left->index[brother_left->length + i + 1] = node->index[i + 1];
		if (brother_left->index[brother_left->length + i + 1])
			brother_left->index[brother_left->length + i + 1]->parent = brother_left;
	}
	brother_left->length += node->length;
	parent->key[position] = NULL;
	parent->index[position+1] = nullptr;
	--parent->length;
	delete node;
	//for (int j = position; j < parent->length; ++j) 
	//{// 左移
	//	parent->key[j] = parent->key[j + 1];
	//	parent->index[j] = parent->index[j + 1];
	//}
	//parent->index[parent->length] = NULL;
	if (tree->root == parent)
	{/// 如果此时父节点为根，则当父节点没有关键字时才调整
		if (parent->length == 0)
		{
			B_Node* del = parent;
			for (int i = 0; i <= parent->length; ++i) 
			{
				if (parent->index[i]) 
				{
					tree->root = parent->index[i];
					delete del;
					break;
				}
				tree->root->parent = NULL;
			}
		}
	}
	else
	{/// 如果父节点不为根，则需要判断是否需要重新调整
		if (parent->length < tree->order/2) 
			RestoreBTree(tree, parent);
	}
}
static void Merger_Brother_Right(B_Tree* tree, B_Node* brother_right, B_Node* parent, B_Node* node, int position)
{
	for (int i = brother_right->length; i > 0; --i) {
		if (i > 0) {
			brother_right->key[i + 1 + node->length] = brother_right->key[i];
		}
		brother_right->index[i + 1 + node->length] = brother_right->index[i];
	}
	brother_right->key[node->length + 1] = parent->key[position + 1];     // 把父节点分割两个本兄弟和右兄弟的关键字拿下来使用
	for (int i = 0; i <= node->length; ++i) {
		// 把本结点的关键字及子树指针移动到右兄弟中去
		if (i > 0) {
			brother_right->key[i] = node->key[i];
		}
		brother_right->index[i] = node->index[i];
		if (brother_right->index[i]) {
			brother_right->index[i]->parent = brother_right;        // 给右兄弟的节点需要把其父节点指向右兄弟
		}
	}
	brother_right->length += (node->length + 1);
	parent->index[position] = NULL;
	free(node);
	for (int i = position; i < parent->length; ++i) {
		if (i > position) {
			parent->key[i] = parent->key[i + 1];
		}
		parent->index[i] = parent->index[i + 1];
	}
	if (parent->length == 1) 
		// 如果父结点在关键字减少之前只有一个结点，那么需要把父结点的右孩子赋值给左孩子
		parent->index[0] = parent->index[1];
	parent->index[parent->length] = NULL;
	parent->length--;           // 父节点关键字数减1
	if (tree->root == parent) 
	{
		//如果此时父结点为根，则当父结点没有关键字时才调整
		if (parent->length == 0) 
		{
			for (int i = 0; i <= parent->length; ++i) 
			{
				if (parent->index[i]) 
				{
					tree->root = parent->index[i];
					break;
				}
			}
			tree->root->parent = NULL;
		}
	}
	else {
		// 如果父结点不为根，则需要判断是否需要重新调整
		if (parent->length < tree->order/2 )
			RestoreBTree(tree, parent);
	}
}

static void RestoreBTree(B_Tree* tree, B_Node* node)
{
	B_Node* parent, * brother_left, * brother_right;
	parent = node->parent;
	if (parent)
	{///父节点存在
		int i_index;	//i_pos = i_index - 1?
		///找父节点中的父元素,以找到兄弟节点
		for (i_index = 0; i_index <= parent->length; ++i_index)
			if (parent->index[i_index] == node)
				break;
			///parent->index[i_index] 指向当前节点
		brother_left = i_index > 0 ? parent->index[i_index -1] : nullptr;
		brother_right = i_index <= parent->length ? parent->index[i_index+1] : nullptr;

		if
		(///左或右兄弟存在多余元素可借
			brother_left && brother_left->length > tree->order / 2
			||
			brother_right && brother_right->length > tree->order / 2
		)
			BorrowFromBrothers(node,brother_left,brother_right,parent, i_index);
		else
		{///无法借元素，只能合并
			if (brother_left)
				Merger_Brother_Left(tree,brother_left,parent,node, i_index-1);
			else if (brother_right)
				Merger_Brother_Right(tree,brother_left,parent,node, i_index-1);
			else
			{///左右兄弟都不存在，合并当前元素到根节点
				for (int i = 0; i > node->length; ++i)
				{
					if (node->index[i])
					{
						tree->root = node->index[i];
						break;
					}
				}
				tree->root->parent = nullptr;
			}
		}
	}
	else
	{///父节点不存在，即为根节点，合并并减少一层树的高度
		B_Node* del;
		for(int i=0;i<=node->length;++i)
			if (node->index[i + 1])
			{
				del = node;
				node = node->index[i + 1];
				del->index[i] = nullptr;
				delete del;
				break;
			}
		tree->root = node;
		tree->root->parent = nullptr;
	}
}
static void Delete(B_Tree* tree, B_Node* node, int position)
{///position为删除元素key的下标
	if (node->index[position+1])///若元素存在右指针，则非叶节点
	{///删除非叶节点
		///用逻辑后继节点代替(父节点元素代替，父节点用右子树第一个代替)
		B_Node* leaf = node;
		if (leaf)
		{///右孩子的第一个叶子元素(递归)
			leaf = leaf->index[position+1];
			while (leaf->index[0])
				leaf = leaf->index[0];
			node->key[position] = leaf->key[0];
		}
		Delete(tree, leaf, 0);		///删除逻辑后继
	}
	else
	{///删除叶节点
		
		for (int i = position; i < node->length; ++i)
		{///直接删除
			node->key[i] = node->key[i+1];		///因为key末尾预留，且插入时置为0，所以可以直接从后覆盖前，且不考虑越界
			node->index[i] = node->index[i+1];
		}
		--node->length;
		if (node->length < node->maxsize / 2)	///阈值可自定义
			RestoreBTree(tree, node);///调整B树
	}
}
//删除值为key的元素
void B_Tree_Delete(B_Tree* tree, int key)
{
	Result result = B_Tree_Search(tree, key);
	if (result.tag)
	{///result查找key成功时，返回key所在的节点和下标
		Delete(tree, result.index, result.pos);
		--tree->count;
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










