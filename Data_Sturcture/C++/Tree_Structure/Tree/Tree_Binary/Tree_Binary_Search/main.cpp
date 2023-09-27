
#include "Binary_Tree_Search_Normal/Binary_Tree_Search_Normal.h"
#include "Tree_Binary_Search_AVL/Tree_Binary_Search_AVL.h"
#include "Tree_Binary_Search_BRT/Tree_Binary_Search_BRT.h"

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


//void BinarySearch()
//{
//	Tree_Binary_Search_Normal<int> tree;
//	Node_BinaryTree<int>* d = tree.Node_Create("4",4);
//
//	tree.Tree_Set_Root(d);
//
//	//tree.Tree_Element_Insert(2);
//	//tree.Tree_Element_Insert(1);
//	//tree.Tree_Element_Insert(3);
//	//tree.Tree_Element_Insert(6);
//	//tree.Tree_Element_Insert(5);
//	//tree.Tree_Element_Insert(7);
//
//	tree.Tree_Element_Insert_NonRecursive(2);
//	tree.Tree_Element_Insert_NonRecursive(1);
//	tree.Tree_Element_Insert_NonRecursive(3);
//	tree.Tree_Element_Insert_NonRecursive(6);
//	tree.Tree_Element_Insert_NonRecursive(5);
//	tree.Tree_Element_Insert_NonRecursive(7);
//
//
//	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());
//
//	auto node = tree.Tree_Element_Locate("7");///查找测试
//	if (node)
//		std::cout << "Node Founded" << std::endl;
//	else
//		std::cout << "Node Not Found" << std::endl;
//
//	tree.Tree_Element_Delete(2);
//	std::cout << "After Delete 2" << std::endl;
//	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());
//	tree.Tree_Element_Delete(4);
//	std::cout << "After Delete 4" << std::endl;
//	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());
//
//}

//void BinarySearch_AVL()
//{
//	Tree_Binary_Search_AVL<int> tree;
//	tree.BinaryTree_Insert_AVL(8);
//	tree.BinaryTree_Insert_AVL(4);
//	tree.BinaryTree_Insert_AVL(2);
//	tree.BinaryTree_Insert_AVL(6);
//	tree.BinaryTree_Insert_AVL(9);
//	//std::cout << Tree->num << std::endl;
//	tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
//	tree.BinaryTree_AVL_Delete(tree.root, 8);
//	std::cout << std::endl;
//	tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
//}
//
//void BinarySearch_RBT()
//{
//	Tree_Binary_Search_RBT<int> tree;
//
//	Node_Binary_Search_RB<int>* a = tree.RBNode_Create(8);
//	Node_Binary_Search_RB<int>* b = tree.RBNode_Create(5);
//	Node_Binary_Search_RB<int>* c = tree.RBNode_Create(15);
//	Node_Binary_Search_RB<int>* d = tree.RBNode_Create(12);
//	Node_Binary_Search_RB<int>* e = tree.RBNode_Create(19);
//	Node_Binary_Search_RB<int>* f = tree.RBNode_Create(9);
//	Node_Binary_Search_RB<int>* g = tree.RBNode_Create(13);
//	Node_Binary_Search_RB<int>* h = tree.RBNode_Create(23);
//
//	tree.RBTree_RBNode_Insert(a);
//	tree.RBTree_RBNode_Insert(b);
//	tree.RBTree_RBNode_Insert(c);
//	tree.RBTree_RBNode_Insert(d);///叔红 变色父、祖父、叔节点
//	tree.RBTree_RBNode_Insert(e);
//	tree.RBTree_RBNode_Insert(f);///叔红 变色父、祖父、叔节点
//	tree.RBTree_RBNode_Insert(g);
//	tree.RBTree_RBNode_Insert(h);
//	///叔红->变色;切换视角为12节点 RL->右旋父节点+左旋祖父节点+变色父、祖父
//
//	std::cout << "\nDLR:";
//	tree.RBTree_Traverse_Preorder(tree.root);
//
//	tree.RBTree_RBNode_Delete(15);
//	tree.RBTree_RBNode_Delete(19);
//	tree.RBTree_RBNode_Delete(13);
//	tree.RBTree_RBNode_Delete(23);
//
//
//
//	std::cout << std::endl << "After Delete 15 19 13 23" << std::endl;
//	std::cout << "\nDLR:";
//	tree.RBTree_Traverse_Preorder(tree.root);
//	std::cout << "\nLDR:";
//	tree.RBTree_Traverse_Inorder(tree.root);
//
//	std::cout << std::endl << "\n搜索节点9：目标节点值为" << tree.RBTree_Search(9)->element;
//
//}

//void TestBinarySearch()
//{
//	//Tree_Binary_Search<int, int, Node_Binary_Search_Normal<int, int>>* tree = new Tree_Binary_Search_Normal<int, int, Node_Binary_Search_Normal<int, int>>();
//	//Tree_Binary_Search<int, int, Node_Binary_Search_Balance<int, int>>* tree = new Tree_Binary_Search_AVL<int, int>();
//	Tree_Binary_Search<int, int, Node_Binary_Search_RB<int, int>>* tree = new Tree_Binary_Search_RBT<int, int>();
//
//	
//	//tree->Element_Insert(4);
//	//tree->Element_Insert(2);
//	//tree->Element_Insert(1);
//	//tree->Element_Insert(3);
//	//tree->Element_Insert(6);
//	//tree->Element_Insert(5);
//	//tree->Element_Insert(7);
//
//	tree->Element_Insert(8);
//	tree->Element_Insert(5);
//	tree->Element_Insert(15);
//	tree->Element_Insert(12);
//	tree->Element_Insert(19);
//	tree->Element_Insert(9);
//	tree->Element_Insert(13);
//	tree->Element_Insert(23);
//
//	tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());
//
//	//std::cout << std::endl << "Search node: name == \"7\"" << std::endl;
//	//auto node = tree->Node_Search(7);///查找测试
//	//std::cout << ((node->key == 7) ? "Node Founded" : "Node Not Found") << std::endl;
//
//	tree->Element_Delete(15);
//	tree->Element_Delete(19);
//	tree->Element_Delete(13);
//	tree->Element_Delete(23);
//						 
//	//std::cout << std::endl;
//	//tree->Element_Delete(2);
//	//std::cout << "After Delete 2" << std::endl;
//	//tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());
//	//tree->Element_Delete(4);
//	std::cout << std::endl;
//	//std::cout << "After Delete 4" << std::endl;
//	tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());
//
//}

void TestBinarySearch()
{
	//Tree_Binary_Search<int, int, Node_Binary_Search_Normal<int, int>>* tree = new Tree_Binary_Search_Normal<int, int, Node_Binary_Search_Normal<int, int>>();
	Tree_Binary_Search<int, int, Node_Binary_Search_Balance<int, int>>* tree = new Tree_Binary_Search_AVL<int, int>();
	//Tree_Binary_Search<int, int, Node_Binary_Search_RB<int, int>>* tree = new Tree_Binary_Search_RBT<int, int>();


	for (int i = 1; i <= 18; ++i)
		tree->Element_Insert(i, i);
	tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());

	std::cout << std::endl;
	auto node = tree->Node_Search(15);
	if (node)
		std::cout << "Finding node whick key == 15 : " << ((node->key == 15) ? "Succeed" : "Failed") << std::endl;
	std::cout <<"Node 7 has element: " << tree->Element_Get(tree->Node_Search(7));

	for (int i = 10; i > 5; --i)
		tree->Element_Delete(i);

	std::cout << std::endl;
	std::cout << "After delete 6-10" << std::endl;
	std::cout << std::endl << "PreOrder Traverse" << std::endl;
	tree->Tree_Traverse_PreOrder(tree->Tree_GetRoot());
	std::cout << std::endl << "InOrder Traverse" << std::endl;
	tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());
	std::cout << std::endl << "PostOrder Traverse" << std::endl;
	tree->Tree_Traverse_PostOrder(tree->Tree_GetRoot());
	std::cout << std::endl << "LevelOrder Traverse" << std::endl;
	tree->Tree_Traverse_LevelOrder(tree->Tree_GetRoot());

	std::cout << std::endl;
	delete tree;
}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//BinarySearch();
	//BinarySearch_AVL();
	//BinarySearch_RBT();
	TestBinarySearch();
}