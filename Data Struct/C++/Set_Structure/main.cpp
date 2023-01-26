
#include <iostream>

#include "Set_Hash_LinearDetection.h"
#include "Set_Hash_LinkAddress.h"

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

void TestHashList_LinearDetection()
{
	//线性探测法解决冲突
	std::cout << "线性探测法解决冲突" << std::endl;
	HashList<int> h(5);
	h.HashList_Show();
	h.HashList_Insert(1);
	h.HashList_Insert(2);
	h.HashList_Insert(7);
	h.HashList_Insert(12);
	h.HashList_Insert(17);
	h.HashList_Show();

	std::cout << "key为12的下标索引为:" << h.HashList_Locate(12) << std::endl;
	std::cout << "key为2的下标索引为:" << h.HashList_Locate(2) << std::endl;
	std::cout << "key为17的下标索引为:" << h.HashList_Locate(17) << std::endl;
	
}

void TestHashList_LinkAddress()
{
	//链地址法解决冲突
	std::cout << "链地址法解决冲突" << std::endl;
	HashList_Link<int> h(5);
	h.HashList_Show();

	h.HashList_Insert(1);
	h.HashList_Insert(2);
	h.HashList_Insert(3);
	h.HashList_Insert(4);
	h.HashList_Insert(5);
	h.HashList_Insert(7);
	h.HashList_Insert(12);
	h.HashList_Insert(23);
	h.HashList_Show();

	std::cout << "key为12的下标索引为:" << h.HashList_Locate(12) << std::endl;
	std::cout << "key为23的下标索引为:" << h.HashList_Locate(23) << std::endl;
}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	
	//TestHashList_LinearDetection();
	TestHashList_LinkAddress();
}
