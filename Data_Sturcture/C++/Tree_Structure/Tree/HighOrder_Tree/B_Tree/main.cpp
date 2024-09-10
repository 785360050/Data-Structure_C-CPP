

#ifdef _WIN32
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
#endif



#include "Tree_B.hpp"


// 好像有bug，晚点再看
// main: malloc.c:2617: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
void Test_B_Tree()
{
	Tree_Advanced_B<int,int,5> tree;

	for (int i = 1; i < 23; ++i)
	{
		tree.Element_Insert(i);
		//B_Tree_Show(tree, "");
	}
	tree.B_Tree_Show("After Insert 1-20");

	tree.Element_Delete(20);
	tree.B_Tree_Show("After Delete 20");
	tree.Element_Delete(14);
	tree.B_Tree_Show("After Delete 14");
	tree.Element_Delete(15);
	tree.B_Tree_Show("After Delete 15");
	tree.Element_Delete(17);
	tree.B_Tree_Show("After Delete 17");
	tree.Element_Delete(2);
	tree.B_Tree_Show("After Delete 2");
	tree.Element_Delete(7);
	tree.B_Tree_Show("After Delete 7");
	tree.Element_Delete(9);
	tree.B_Tree_Show("After Delete 9");

	std::cout << std::endl;
}

/// 未完成
#include "Tree_B+.hpp"
void Test_BPlus_Tree()
{
	BPlus_Tree<int> tree;
	for (int i = 1; i < 23; i++)
	// for (int i = 1; i < 60; i++)
	{
		tree.Element_Insert(i, i);
		std::cout << std::endl;
		tree.Show();
	}
	tree.Show();

	printf("\n删除元素\n");

	// tree.Element_Delete(37);
	// tree.Show();

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


}


int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	// Test_B_Tree();
	Test_BPlus_Tree();

	return EXIT_SUCCESS;
}
