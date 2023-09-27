
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
#include "Tree_B+.hpp"

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


///未完成
void Test_BPlus_Tree()
{
	BPlus_Tree<int> tree;
	//for (int i = 0; i < 30; i++)
	for (int i = 0; i < 60; i++)
	{
		tree.Element_Insert(i, i);
		std::cout << std::endl;
		tree.Show();
	}

	printf("\n删除元素\n");

	tree.Element_Delete(37);
	tree.Show();

	tree.Element_Delete(1);
	tree.Show();
	tree.Element_Delete(2);
	tree.Show();
	tree.Element_Delete(3);
	tree.Show();
	tree.Element_Delete(4);
	tree.Show();
	tree.Element_Delete(5);
	tree.Show();
	tree.Element_Delete(6);
	tree.Show();
	tree.Element_Delete(7);
	tree.Show();
	tree.Element_Delete(8);
	tree.Show();
	tree.Element_Delete(9);
	tree.Show();
	tree.Element_Delete(10);
	tree.Show();
	tree.Element_Delete(11);
	tree.Show();
	tree.Element_Delete(12);
	tree.Show();
	tree.Element_Delete(26);
	tree.Show();
	tree.Element_Delete(25);
	tree.Show();
	tree.Element_Delete(23);
	tree.Show();
	tree.Element_Delete(22);
	tree.Show();
	tree.Element_Delete(18);//没有修改根节点数据
	tree.Show();
	tree.Element_Delete(21);
	tree.Show();

	//for (int i = 1; i < 30; i += 2)
	//	BPlus_Tree_Insert(tree, i, i);
	//tree.Show();

	//tree.Element_Delete(0);
	//tree.Show();
	//tree.Element_Delete(9);
	//tree.Show();
	//tree.Element_Delete(17);
	//tree.Show();
	//tree.Element_Delete(21);
	//tree.Show();

	for (int i = 0; i < 60; ++i)
	{
		auto v = tree.Search(i);
		if (v.has_value())
			std::cout << "Key " << i << ':' << v.value() << std::endl;
		else
			std::cout << "Key " << i << "Not Found" << std::endl;
	}

	//BPlus_Tree_Destroy(tree);
}


void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//Test_B_Tree();
	Test_BPlus_Tree();
}

