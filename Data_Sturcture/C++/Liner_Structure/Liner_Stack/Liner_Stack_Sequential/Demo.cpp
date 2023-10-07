#include "Sequential_Stack.hpp"

#ifdef _Win32 // ARM32/64, x86/x64
// 详见 https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
#include <Windows.h>
/// 修改cmd编码方式
static bool SetEncode(int EncodeId = 936)
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

void TestSequenceStack()
{
	Sequential_Stack<char, 5> s;				 /// 空增栈
	// Sequential_Stack_Full_Ascending<char, 5> s;	 /// 满增栈
	// Sequential_Stack_Empty_Descending<char, 5> s; /// 空减栈  (缺陷：栈满时size_t top值必定下溢)
	// Sequential_Stack_Full_Descending<char, 5> s;	 /// 满减栈
	s.Stack_Show("初始化5个单位的栈空间后：");
	
	for (int i = 65; i < 70; i++)
		s.Element_Push(i);
	s.Stack_Show("压入5个元素后：");
	// s.Stack_Clear();
	std::cout << "当前栈顶元素为：" << s.Get_Top() << std::endl;
	std::cout << "当前栈元素数量为：" << s.Get_Size() << std::endl;
	std::cout << "栈判空：" << std::boolalpha << s.Is_Empty() << std::endl;
	while (s.Get_Size() > 0)
	{
		std::cout << s.Get_Top() << "出栈" << std::endl;
		s.Element_Pop();
	}

	std::cout << "栈判空：" << std::boolalpha << s.Is_Empty() << std::endl;
}

int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	TestSequenceStack();
	return EXIT_SUCCESS;
}