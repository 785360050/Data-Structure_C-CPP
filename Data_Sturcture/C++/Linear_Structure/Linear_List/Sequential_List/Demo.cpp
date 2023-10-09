#include <iostream>

// #include "Linear_List_ADT.h"
#include "Sequential_List.hpp"

#ifdef _WIN32
#include <Windows.h>
/// 修改cmd编码方式
static bool SetEncode(int EncodeId = 936)
{
	/// <summary>
	/// EncodeId 是代码页,设置它等于设置我们指定的编码格式。
	///	默认936为unicode编码
	/// SetConsoleCP() 设置控制台输入时使用的编码。
	///	SetConsoleOutputCP() 设置控制台输出时使用的编码。
	/// </summary>
	/// <param name="EncodeId"></param>
	/// <returns></returns>
	return SetConsoleCP(EncodeId) && SetConsoleOutputCP(EncodeId);
}
#endif

// void Test_SeqList_Array()
// {
// 	std::cout << "[Static Sequential List]" << std::endl;
// 	Sequential_List_Array<int> L(5);
// 	L.List_Show("初始化5个元素空间的顺序表后");
// 	std::cout << std::endl;

// 	for (int i = 1; i <= 5; i++)
// 		L.Element_Insert(i, i);
// 	L.List_Show("插入5个元素后");
// 	std::cout << std::endl;

// 	try
// 	{
// 		L.Element_Insert(2, 9);
// 	}
// 	catch (const std::runtime_error &e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}

// 	L.List_Show("第二个位置插入9后,检测到存储空间已满,捕获异常");
// 	std::cout << std::endl;

// 	try
// 	{
// 		L.Element_Insert(20, 20);
// 	}
// 	catch (const std::runtime_error &e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
// 	L.List_Show("第20个非法位置插入20后,捕获异常");
// 	std::cout << std::endl;

// 	L.Element_Update(2, 999);
// 	L.List_Show("第二个元素改为999后");
// 	std::cout << std::endl;

// 	int del;
// 	del = L.Element_Delete(2);
// 	L.List_Show("删除第二个元素后");
// 	std::cout << "删除的第二个元素为:" << del << std::endl;

// 	std::cout << "获取第二个元素值:" << L.List_GetData(2) << std::endl;

// 	std::cout << "判空:" << std::boolalpha << L.List_CheckEmpty() << std::endl;
// 	std::cout << "当前表长：" << L.List_GetLength() << std::endl;
// 	L.List_Clear();
// 	L.List_Show("清空后");
// 	std::cout << "当前表长：" << L.List_GetLength() << std::endl;
// }

void Test_SeqList_Static()
{
	std::cout << "[Static Sequential List]" << std::endl;
	Sequential_List_Static<int,5> L;
	L.List_Show("初始化5个元素空间的顺序表后");
	std::cout << std::endl;

	for (int i = 1; i <= 5; i++)
		L.Element_Insert(i, i);
	L.List_Show("插入5个元素后");
	std::cout << std::endl;

	try
	{
		L.Element_Insert(2, 9);
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << e.what() << '\n';
	}

	L.List_Show("第二个位置插入9后,检测到存储空间已满,捕获异常");
	std::cout << std::endl;

	try
	{
		L.Element_Insert(20, 20);
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << e.what() << '\n';
	}
	L.List_Show("第20个非法位置插入20后,捕获异常");
	std::cout << std::endl;

	L.Element_Update(2, 999);
	L.List_Show("第二个元素改为999后");
	std::cout << std::endl;

	int del=L[2];
	L.Element_Delete(2);
	L.List_Show("删除第二个元素后");
	std::cout << "删除的第二个元素为:" << del << std::endl;

	std::cout << "获取第二个元素值:" << L[2] << std::endl;

	std::cout << "判空:" << std::boolalpha << L.Is_Empty() << std::endl;
	std::cout << "当前表长：" << L.Get_Size() << std::endl;
	L.List_Clear();
	L.List_Show("清空后");
	std::cout << "当前表长：" << L.Get_Size() << std::endl;
}

void Test_SeqList_Dynamic()
{
	using namespace std;
	std::cout << "[Dynamic Sequential List]" << std::endl;
	Sequential_List_Dynamic<int> L(5);
	L.List_Show("初始化5个元素空间的顺序表后");
//
	std::cout << std::endl;

	for (int i = 1; i <= 5; i++)
		L.Element_Insert(i, i);
	L.List_Show("插入5个元素后");
	std::cout << std::endl;

	L.Element_Insert(2, 9);
	L.List_Show("第二个位置插入9后,检测到存储空间已满,扩展空间");
	std::cout << std::endl;

	std::cout << std::endl;
	L.Element_Insert(20, 20);
	L.List_Show("第20个非法位置插入20后");
	std::cout << std::endl;
	L.Element_Update(2, 999);
	L.List_Show("第二个元素改为999后");
	std::cout << std::endl;

	int del = std::move(L[2]);
	L.Element_Delete(2);
	L.List_Show("删除第二个元素后，自动收缩存储空间");
	std::cout << "删除的第二个元素为:" << del << std::endl;

	std::cout << "获取第二个元素值:" << L[2] << std::endl;
	std::cout << std::endl;

	for (size_t i = 5; i > 2; --i)
		L.Element_Delete(i);
	L.List_Show("删除3个元素后,再次收缩存储空间");
	std::cout << std::endl;

	std::cout << "判空 :" << boolalpha << L.Is_Empty() << std::endl;
	std::cout << "当前表长：" << L.Get_Capcity() << std::endl;
	L.List_Clear();
	L.List_Show("清空后");
	//
	std::cout << "当前表长：" << L.Get_Size() << std::endl;
}

int main()
{
	//  SetEncode(65001);//设置控制台为utf-8编码格式
	Test_SeqList_Static();
	Test_SeqList_Dynamic();
	
	return EXIT_SUCCESS;
}
