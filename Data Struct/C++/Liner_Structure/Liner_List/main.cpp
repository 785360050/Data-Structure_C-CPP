

#include "Liner_List_ADT.h"
#include "Liner_List_Sequential/Liner_List_Sequential.h"
#include "Liner_List_Link/Link_List.h"
#include <memory>


#include <Windows.h>
///修改cmd编码方式
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



void Test_SeqList()
{
	//std::unique_ptr<Liner_List<int, int>> seq_list = std::make_unique<Sequential_List_Array<int>>(5);
	Liner_List<int, int>* seq_list = new Sequential_List_Array<int>(5);
	//Liner_List<int, int>* seq_list = new Sequential_List_Vector<int>(5);
	seq_list->List_Show("Initialize");

	for (int i = 1; i <= 5; i++)
		seq_list->Element_Insert(i, i);
	seq_list->List_Show("插入5个元素后");


	seq_list->Element_Insert(2, 9);
	seq_list->List_Show("第二个位置插入9后，检测到存储空间已满，报错");

	std::cout << std::endl;
	seq_list->Element_Insert(20, 20);
	seq_list->List_Show("第20个非法位置插入20后");

	std::cout << std::endl;
	seq_list->Element_Update(2, 999);
	seq_list->List_Show("第二个元素改为999后");

	int del;
	del = seq_list->Element_Delete(2);
	seq_list->List_Show("删除第二个元素后");
	std::cout << "删除的第二个元素为:" << del << std::endl;

	std::cout << "获取第二个元素值:" << seq_list->List_GetData(2) << std::endl;

	std::cout << "判空:" << std::boolalpha << seq_list->List_CheckEmpty() << std::endl;
	std::cout << "当前表长：" << seq_list->List_GetLength() << std::endl;
	seq_list->List_Clear();
	seq_list->List_Show("清空后");
	std::cout << "当前表长：" << seq_list->List_GetLength() << std::endl;

	//delete seq_list;
}

void Test_LinkList()
{
	//std::unique_ptr<Liner_List<List_Node_SingleWay<int>, int>> link_list = std::make_unique<Link_List_Forward<int>>();
	Liner_List<List_Node_SingleWay<int>, int>* link_list = new Link_List_Forward<int>;
	//Liner_List<List_Node_DoubleWay<int>, int>* link_list = new Link_List_Double<int>;
	link_list->List_Show("Initialize");

	for (int i = 1; i <= 5; i++)
		link_list->Element_Insert(i, i);
	link_list->List_Show("插入5个元素后");


	link_list->Element_Insert(2, 9);
	link_list->List_Show("第二个位置插入9后，链表扩展一个元素");

	std::cout << std::endl;
	link_list->Element_Insert(20, 20);
	link_list->List_Show("第20个非法位置插入20后");

	std::cout << std::endl;
	link_list->Element_Update(2, 999);
	link_list->List_Show("第二个元素改为999后");

	int del;
	del = link_list->Element_Delete(2);
	link_list->List_Show("删除第二个元素后");
	std::cout << "删除的第二个元素为:" << del << std::endl;

	std::cout << "获取第二个元素值:" << link_list->List_GetData(2) << std::endl;

	std::cout << "判空:" << std::boolalpha << link_list->List_CheckEmpty() << std::endl;
	std::cout << "当前表长：" << link_list->List_GetLength() << std::endl;
	link_list->List_Clear();
	link_list->List_Show("元素重置后");
	std::cout << "当前表长：" << link_list->List_GetLength() << std::endl;

	delete link_list;
}


void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//Test_SeqList();
	Test_LinkList();
}
