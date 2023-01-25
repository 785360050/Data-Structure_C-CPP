
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

#include "MergeFindSet_ADT.h"
#include "MergeFindSet_QuickFind.h"
#include "MergeFindSet_QuickMerge.h"

void QuickFind_MergeFindSet()
{
	int* data = new int[5] {0, 1, 2, 3, 4};		///仅支持堆空间的数组，Set析构时释放

	MergeFindSet_QuickFind<int> set_QF(data, 5);
	set_QF.Merge(0, 2);
	set_QF.Merge(4, 2);
	std::cout << set_QF.Find(0, 2) << std::endl;
	std::cout << set_QF.Find(1, 2) << std::endl;
	set_QF.Show();
}

void QuickMerge_MergeFindSet()
{
	int* data = new int[5] {0, 1, 2, 3, 4};		///仅支持堆空间的数组，Set析构时释放

	MergeFindSet_QuickMerge<int> set_QM(data, 5);

	set_QM.Show();
	set_QM.Merge(0, 2);
	set_QM.Merge(4, 2);
	set_QM.Merge(1, 3);
	std::cout << set_QM.Find(0, 2) << std::endl;
	std::cout << set_QM.Find(1, 2) << std::endl;
	set_QM.Show();
	std::cout << "RootIndex(2)= " << set_QM.RootIndex(2) << std::endl;
	std::cout << "RootIndex(2)= " << set_QM.RootIndex_Optimized(2) << std::endl;

}


void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//QuickFind_MergeFindSet();
	QuickMerge_MergeFindSet();
}

