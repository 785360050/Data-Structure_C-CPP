

#include "Binary_Heap.hpp"


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

/// @brief CmpareMethod模板参数是从数组左到右(树根->树叶)比较的，如std::less就是小根堆
void TestHeap()
{
	Binary_Heap<int, 10, std::greater<>> heap;//大根堆
	heap.Heap_Show();

	for (int i = 1; i <= 10; ++i)
		heap.Push(i);

	heap.Heap_Show();
	
	std::cout << "TOP = " << heap.Get_Top() << std::endl;

	for (int i = 0; i < 5; ++i)
	{
		heap.Pop();
		std::cout << "After Pop top" << std::endl;
		heap.Heap_Show();
	}


}



int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	TestHeap();

	return EXIT_SUCCESS;
}