

#ifdef _Win32 // ARM32/64, x86/x64
// 详见 https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
#include <Windows.hpp>
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

#include "MergeFindSet.hpp"
#include "MergeFindSet_QuickFind.hpp"
// #include "MergeFindSet_QuickMerge.hpp"

void TestMergeFindSet()
{
	int* data = new int[5] {0, 1, 2, 3, 4};		///仅支持堆空间的数组，Set析构时释放

	MergeFindSet_QuickFind<int> set(data, 5);
	// MergeFindSet_QuickMerge<int> set(data, 5);
	std::cout << "初始化5个元素后" << std::endl;
	set.Show();

	set.Merge(0, 2);
	set.Merge(4, 2);
	std::cout << "合并0,2和4,2后" << std::endl;
	set.Show();
	std::cout << "判断0和2是否在同一组: " << std::boolalpha << set.Find(0, 2) << std::endl;
	std::cout << "判断1和2是否在同一组: " << std::boolalpha << set.Find(1, 2) << std::endl;
	//set.Show();

	//std::cout << "RootIndex(2)= " << set.RootIndex(2) << std::endl;
	//std::cout << "RootIndex(2)= " << set.RootIndex_Optimized(2) << std::endl;
}



int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	TestMergeFindSet();

	return EXIT_SUCCESS;
}
