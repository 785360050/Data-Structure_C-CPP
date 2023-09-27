
#include "Tree_Binary_Search_BRT.h"

#include <Windows.h>
static bool  SetEncode(int EncodeId = 936)
{
	/// <summary>
	/// EncodeId 是代码页，设置它等于设置我们指定的编码格式。
	///	默认936为unicode编码
	/// SetConsoleCP() 设置控制台输入时使用的编码。
	///	SetConsoleOutputCP() 设置控制台输出时使用的编码。
	/// </summary>
	/// <param name="EncodeId"></param>
	/// <returns></returns>
	return SetConsoleCP(EncodeId) && SetConsoleOutputCP(EncodeId);
}

void BinarySearch_RBT()
{
	Tree_Binary_Search_RBT<int> tree;

	Node_Binary_Search_RB<int>* a = tree.RBNode_Create(8);
	Node_Binary_Search_RB<int>* b = tree.RBNode_Create(5);
	Node_Binary_Search_RB<int>* c = tree.RBNode_Create(15);
	Node_Binary_Search_RB<int>* d = tree.RBNode_Create(12);
	Node_Binary_Search_RB<int>* e = tree.RBNode_Create(19);
	Node_Binary_Search_RB<int>* f = tree.RBNode_Create(9);
	Node_Binary_Search_RB<int>* g = tree.RBNode_Create(13);
	Node_Binary_Search_RB<int>* h = tree.RBNode_Create(23);

	tree.RBTree_RBNode_Insert(a);
	tree.RBTree_RBNode_Insert(b);
	tree.RBTree_RBNode_Insert(c);
	tree.RBTree_RBNode_Insert(d);///叔红 变色父、祖父、叔节点
	tree.RBTree_RBNode_Insert(e);
	tree.RBTree_RBNode_Insert(f);///叔红 变色父、祖父、叔节点
	tree.RBTree_RBNode_Insert(g);
	tree.RBTree_RBNode_Insert(h);
	///叔红->变色;切换视角为12节点 RL->右旋父节点+左旋祖父节点+变色父、祖父

	std::cout << "\nDLR:";
	tree.RBTree_Traverse_Preorder(tree.root);

	tree.RBTree_RBNode_Delete(15);
	tree.RBTree_RBNode_Delete(19);
	tree.RBTree_RBNode_Delete(13);
	tree.RBTree_RBNode_Delete(23);



	std::cout << std::endl << "After Delete 15 19 13 23" << std::endl;
	std::cout << "\nDLR:";
	tree.RBTree_Traverse_Preorder(tree.root);
	std::cout << "\nLDR:";
	tree.RBTree_Traverse_Inorder(tree.root);

	std::cout << std::endl << "\n搜索节点9：目标节点值为" << tree.RBTree_Search(9)->element;

}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	BinarySearch_RBT();
}