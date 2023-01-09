#include <iostream>

//#include "Liner_List_ADT.h"
#include "Liner_List_Sequential.h"





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






void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	using namespace std;
	Sequential_List_Array<int> L(5);
	L.List_Show("初始化5个元素空间的顺序表后");

	for (int i = 1; i <= 5; i++)
		L.Element_Insert(i, i);
	L.List_Show("插入5个元素后");

	L.Element_Insert(2, 9);
	L.List_Show("第二个位置插入9后，检测到存储空间已满，扩展空间");

	std::cout << std::endl;
	L.Element_Insert(20, 20);
	L.List_Show("第20个非法位置插入20后");

	std::cout << std::endl;
	L.Element_Update(2, 999);
	L.List_Show("第二个元素改为999后");

	int del;
	del = L.Element_Delete(2);
	L.List_Show("删除第二个元素后");
	std::cout << "删除的第二个元素为:" << del << std::endl;

	std::cout << "获取第二个元素值:" << L.List_GetElement(2) << std::endl;

	std::cout << "判空 {0=F,1=T}:" << L.List_CheckEmpty() << std::endl;
	std::cout << "当前表长：" << L.List_GetLength() << std::endl;
	L.List_Clear();
	L.List_Show("清空后");
	std::cout << "当前表长：" << L.List_GetLength() << std::endl;

	L.List_Destroy();
}




