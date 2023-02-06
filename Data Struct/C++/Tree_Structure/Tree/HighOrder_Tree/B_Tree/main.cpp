
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




#include "Tree_B.h"
#include "Tree_B+.h"

void Test_B_Tree()
{
	Tree_Advanced_B<int> tree(5);

	for (int i = 1; i < 21; ++i)
	{
		tree.B_Tree_Insert(i);
		//B_Tree_Show(tree, "");
	}
	tree.B_Tree_Show("After Insert 1-20");

	tree.B_Tree_Delete(20);
	tree.B_Tree_Show("After Delete 20");
	tree.B_Tree_Delete(14);
	tree.B_Tree_Show("After Delete 14");
	tree.B_Tree_Delete(15);
	tree.B_Tree_Show("After Delete 15");
	tree.B_Tree_Delete(17);
	tree.B_Tree_Show("After Delete 17");
	tree.B_Tree_Delete(2);
	tree.B_Tree_Show("After Delete 2");
	tree.B_Tree_Delete(7);
	tree.B_Tree_Show("After Delete 7");
	tree.B_Tree_Delete(9);
	tree.B_Tree_Show("After Delete 9");

	std::cout << std::endl;
}

void Test_BPlus_Tree()
{
	BPTree<int, int>* tree = new BPTree<int, int>();
	for (int i = 1; i <= 7; ++i)
		tree->insert(i, i);
	//tree->scan();
	tree->display();
	delete tree;
}


void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//Test_B_Tree();
	Test_BPlus_Tree();
}

