#pragma once



/// <summary>
/// 索引节点中的元素为每个子节点的末尾元素
/// 定义算法等建议看WikiPidia，详细且有存储图，实现上和教材上有些不一样
/// 运行效果见https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html
/// 
/// 总结：
/// B+树的叶子是一个链表
/// 索引节点和叶子节点结构不同，但是此处公用一种struct
/// 索引节点之间类似B—树，
/// 但是索引节点与最底层的叶子节点需要注意：每一个索引元素存叶子节点的分割元素(在叶子上出现的)
///		最底层的索引节点只存右孩子首元素key(最左孩子元素key不存)
///		非最底层的索引节点分割元素时，不同于最底层索引节点，需要像B-树一样将分割元素移到上层
///		(这样效果是高层索引元素也一一对应叶子的右孩子首元素key)
///		
/// 
/// </summary>

struct BPlus_Node
{
	int* keys;			  // 主键 最大max个 最小min个
	int* data;		  // 真实数据  最大max个 最小min个 对于内部结点 data是nullptr
	BPlus_Node** child; // 子节点 最大max+1个 最小min+1个
	BPlus_Node* next;	  // 指向兄弟结点 仅仅是叶子结点的时候才有值
	BPlus_Node* parent;
	int count;			  // 当前元素个数
};


///索引节点元素，取该元素右子树的最小元素(即分割元素)
struct BPlus_Tree
{
	BPlus_Node* root;
	int max;///最大阶数
	int min;///最小阶数(默认写死为 max / 2)
};







///初始化orders阶的B+树，默认每个节点最少为orders/2   (n阶节点最多有n-1个元素)
BPlus_Tree* BPlus_Tree_Init(int orders);

void BPlus_Tree_Destroy(BPlus_Tree* tree);


//创建新的叶子结点
BPlus_Node* BPlus_Node_Create_Leaf(int m);

//创建新的内部结点
BPlus_Node* BPlus_Node_Create_Branch(int m);


void BPlus_Tree_Insert(BPlus_Tree* tree, int key, int value);






void BPlus_Tree_Delete(BPlus_Tree* tree, int key);


void BPlus_Tree_Show(BPlus_Tree* tree);