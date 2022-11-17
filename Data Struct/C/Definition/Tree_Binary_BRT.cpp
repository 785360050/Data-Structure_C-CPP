#include "../API/Tree_Binary_BRT.h"


//左旋
static void Rotate_Left(RBTree* tree, RBNode* node)
{
	RBNode* temp = node->right;
	node->right = temp->left;
	if (temp->left)
		temp->left->partent = node;
	temp->partent = node->partent;
	if (node->partent)
		node->partent->left == node ?
		node->partent->left = temp : node->partent->right = temp;
	else
		tree->root = temp;
	temp->left = node;
	node->partent = temp;
}
//右旋
static void Rotate_Right(RBTree* tree, RBNode* node)
{
	RBNode* temp = node->left;
	node->left = temp->right;
	if (temp->right)
		temp->right->partent = node;
	temp->partent = node->partent;
	if (node->partent)
		node->partent->right == node ?
		node->partent->right = temp : node->partent->left = temp;
	else
		tree->root = temp;
	temp->right = node;
	node->partent = temp;
}

//节点颜色切换
static void Colour_Switch(RBNode* const node)
{
	//node->colour = node->colour == red ? black : red;
	if (node->colour == red)
		node->colour = black;
	else
		node->colour = red;
}

///调整
static void RBTree_Adjust_Insert(RBTree* tree, RBNode* node)
{
	RBNode* parent, * ancestor, * uncle, * temp;//ancestor=GrandParent
	parent = node->partent;
	while (parent && (parent->colour == red))
	{///父节点为红
		ancestor = parent->partent;
		parent == ancestor->left ?///定位uncle节点位置
			uncle = ancestor->right : uncle = ancestor->left;
		if (uncle && uncle->colour == red)
		{///叔节点为红色->父、祖父、叔节点变色
			Colour_Switch(uncle);
			Colour_Switch(ancestor);
			Colour_Switch(parent);
			node = ancestor;
			parent = node->partent;
			continue;
		}
		///叔节点为黑色
		if (ancestor->left == parent)
		{///L
			if (parent->right == node)
			{///LR插入->左旋转父节点为LL
				Rotate_Left(tree, parent);
				temp = parent;
				parent = node;
				node = temp;
			}
			///LL时->右旋祖父节点+变色祖父、父节点
			Rotate_Right(tree, ancestor);
			Colour_Switch(ancestor);
			Colour_Switch(parent);
		}
		else
		{///R
			if (parent->left == node)
			{///RL插入->右旋父节点为RR
				Rotate_Right(tree, parent);
				temp = parent;
				parent = node;
				node = temp;
			}
			///RR时->左旋祖父节点+变色祖父、父节点
			Rotate_Left(tree, ancestor);
			Colour_Switch(ancestor);
			Colour_Switch(parent);
		}
	}
	///插入为根时，跳过所有条件判断变色根节点
	tree->root->colour = black;
}
static void RBTree_Adjust_Delete(RBTree* tree, RBNode* instead, RBNode* parent)
{
	RBNode* brother;
	while 
	(
		tree->root != instead			///instead非根
		&& 
		(!instead || instead->colour == black)	///instead为黑
	)///instead为黑
	{///instead非根节点，且为红色时
		if (parent->left== instead)
		{///instead为左孩子,则brother为右孩子
			brother = parent->right;
			if (brother->colour == red)
			{///兄弟节点为红色时
				/// 父、兄变色，旋转 转为兄黑处理
				//Colour_Switch(brother);
				//Colour_Switch(parent);
				brother->colour = black;
				parent->colour = red;
				Rotate_Left(tree, parent);
				brother = parent->right;
			}
			if ((!brother->left && brother->left->colour == black)	
				&& 
				(!brother || brother->right->colour == black))
			{///兄弟两孩子都为黑色
				///兄弟变红，while执行向上递推处理
				//Colour_Switch(brother);
				brother->colour = red;
				instead = parent;
				parent = instead->partent;
			}
			else
			{///兄弟节点至少有一个为红色
				if (!brother->right || brother->right->colour == black)
				{///LR红时，转为LL红
					//Colour_Switch(brother->left);
					//Colour_Switch(brother);
					brother->left->colour = black;
					brother->colour = red;
					Rotate_Right(tree, brother);
					brother = parent->right;
				}
				///RR红时
				brother->colour = parent->colour;
				//Colour_Switch(brother->right);
				//Colour_Switch(parent);
				brother->right->colour = black;
				parent->colour = black;
				Rotate_Left(tree, parent);
				break;
			}
		}
		else
		{///brother为左孩子,方法同上
			brother = parent->left;
			if (brother->colour == red)
			{///兄弟节点为红色时
				/// 父、兄变色，旋转 转为兄黑处理
				//Colour_Switch(brother);
				//Colour_Switch(parent);
				brother->colour = black;
				parent->colour = red;
				Rotate_Right(tree, parent);
				brother = parent->left;
			}
			if ((!brother->left || brother->left->colour == black) 
				&& 
				(!brother->right || brother->right->colour == black))
			{///兄弟两孩子都为黑色
				///兄弟变红，while执行向上递推处理
				//Colour_Switch(brother);
				//Colour_Switch(instead);
				brother->colour = red;
				instead = parent;
				parent = instead->partent;
			}
			else
			{
				if (!brother->left || brother->left->colour == black)
				{///RL红时，转RR处理
					//Colour_Switch(brother->right);
					//Colour_Switch(brother);
					brother->right->colour = black;
					brother->colour = red;
					Rotate_Left(tree, brother);
					brother = parent->left;

				}
				///RR红时
				brother->colour = parent->colour;
				//Colour_Switch(brother);
				//Colour_Switch(parent);
				brother->left->colour = black;
				parent->colour = black;
				Rotate_Right(tree, parent);
				break;
			}
		}
	}
	if (instead)
		instead->colour = black;
}


RBNode* RBNode_Create(int key, Colour colour)
{
	RBNode* node = new RBNode;
	node->key = key;
	node->left = node->right = node->partent = nullptr;
	node->colour = colour;
	return node;
}

RBTree* BRT_Init(RBNode* root)
{
	RBTree* tree = new RBTree;
	tree->root = root;
	tree->num = 0;
	return tree;
}

void RBTree_RBNode_Insert(RBTree* tree, RBNode* node)
{
	int key = node->key;
	RBNode* current = tree->root, * precursor = nullptr;
	while (current)
	{
		precursor = current;
		if (key < current->key)
			current = current->left;
		else if (key > current->key)
			current = current->right;
		else
		{
			std::cout << "Node Key is existed" << std::endl;
			return;
		}
	}
	node->partent = precursor;
	if (!precursor)///根节点插入
		tree->root = node;
	else
		key < precursor->key ?///判断插入左右位置
			precursor->left = node : precursor->right = node;
	RBTree_Adjust_Insert(tree,node);
	tree->num++;
}

void RBTree_RBNode_Delete(RBTree* tree, int key)
{
	RBNode* node = RBTree_Search(tree, key);
	if (!node)///删除节点不存在
		return;

	RBNode
		* del,		///删除的节点
		* instead,	///替换的节点，覆盖删除的节点del
		* parent;	///父节点

	///————————————————————————
	///定位删除节点
	///————————————————————————
	if (node->left == nullptr || node->right == nullptr)
		del = node;
	else
	{///del度为2时
		//del = node->right;
		//while (del->left)
		//	del = del->left;
		del = node->left;
		while (del->right)///逻辑前驱
			del = del->right;
	}
	///————————————————————————
	///定位替换节点(逻辑前驱)
	///————————————————————————
	instead = del->left ? del->left : del->right;
	parent = del->partent;

	///————————————————————————
	///开始删除
	///————————————————————————
	if (instead)
		instead->partent = parent;
	if (del->partent == nullptr)	///del为根时
		tree->root = instead;		///替换根节点
	//else if (del->partent->left == del)
	//	del->partent->left = instead;
	//else
	//	instead->partent->right = instead;
	else
	{
		if (del->partent->left == del)
			del->partent->left = instead;
		else
			del->partent->right = instead;
	}

	///————————————————————————
	/// 删除del完毕，更新instead值
	///————————————————————————
	if (del != node)
		node->key = del->key;

	///————————————————————————
	///删除红色节点不调整
	///————————————————————————
	if (del->colour == black)	///删除黑色节点时(删除并替换后)
		RBTree_Adjust_Delete(tree, instead, parent);
	delete del;
	tree->num--;
}

RBNode* RBTree_Search(RBTree* tree, int key)
{
	RBNode* node = tree->root;
	while (node)
	{
		if (key < node->key)
			node = node->left;
		else if (key > node->key)
			node = node->right;
		else
			return node;
			
	}
	return nullptr;
}

static void DeleteNode(RBTree* tree, RBNode* node)
{
	if (node)
	{
		DeleteNode(tree, node->left);
		DeleteNode(tree, node->right);
		std::cout << node->key << " ";
		free(node);
		tree->num--;
	}
}
void RBTree_Destroy(RBTree* tree)
{///自下而上递归销毁节点
	if (tree)
	{
		std::cout << "\n删除红黑树节点个数:" << tree->num << std::endl;
		if (tree->root)
			DeleteNode(tree, tree->root);
	}
}

static void RBTree_Visit(const RBNode* const node)
{
	if (node)
		std::cout << '[' << node->key << ':' << (node->colour == black ? 'B' : 'R') << "] ";
}
void RBTree_Traverse_Inorder(RBNode* node)
{
	if (node)
	{
		RBTree_Traverse_Inorder(node->left);//L
		RBTree_Visit(node);//D
		RBTree_Traverse_Inorder(node->right);//R
	}
}
void RBTree_Traverse_Preorder(RBNode* node)
{
	if (node)
	{
		RBTree_Visit(node);//D
		RBTree_Traverse_Preorder(node->left);//L
		RBTree_Traverse_Preorder(node->right);//R
	}
}



