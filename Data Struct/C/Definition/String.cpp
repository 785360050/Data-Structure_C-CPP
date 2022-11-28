#include "../API/String.h"



void String_Init(String& string, const char* cha)
{
	if (string.string_)
		delete[] string.string_;
	int length = 0;
	while (cha[length])
		++length;

	if (length == 0)
	{
		string.string_ = NULL;
		string.length = 0;
	}
	else
	{///依次填入字符
		string.string_ = new char[length + 1];	
		for (int i = 0; i < length; ++i)
			string.string_[i] = cha[i];
		string.string_[length] = 0;
		string.length = length;
	}///需要末尾置0，否则无法cout；

}

void String_Destroy(String& string)
{
	if (string.string_)
		delete[] string.string_;
}

int String_Fetch_Brute_Force(const String& string, const String& Sub_String)
{
	int i_fetch = 0;
	for (; i_fetch < string.length; ++i_fetch)
	{
		int i_sub = 0;
		for (; i_sub < Sub_String.length; ++i_sub)
			if (
				string.string_[i_fetch + i_sub] 
				!= 
				Sub_String.string_[i_sub]
			   )
				break;
		if (i_sub >= Sub_String.length)
			return i_fetch;
	}
	return -1;
}


int String_Fetch_KMP(const String& string, const String& Sub_String)
{
	//int* next = new int[Sub_String.length];
	//{///初始化next数组,存放匹配失败时回退到的i_sub位置
	//	int i_fetch = 1, i_sub = 0;
	//	next[1] = 0;
	//	while (i_fetch < Sub_String.length)
	//	{///初始化next数组，计算各字符的最长前后缀匹配(PMT表)
	//		if
	//			(	i_sub==0||
	//				string.string_[i_fetch]
	//				==
	//				Sub_String.string_[i_sub]
	//			)
	//		{
	//			++i_fetch;
	//			++i_sub;
	//			next[i_fetch] = i_sub;
	//		}
	//		else	///匹配失败时候，回退i_sub
	//		{
	//			i_sub = next[i_sub];	//BUG:i_sub=3时越界
	//		}
	//	}
	//}
	///// <summary>
	////for (int i = 0; i < Sub_String.length; ++i)
	////	std::cout << next[i] << ' ';
	///// 
	///// 
	///// 
	//int i_fetch = 1, i_sub = 1;
	//while (i_fetch <= string.length && 
	//	i_sub <= Sub_String.string_[i_sub])
	//{
	//	if 
	//		(i_sub==0||
	//		string.string_[i_fetch]
	//		== 
	//		Sub_String.string_[i_sub]
	//		)
	//	{
	//		++i_fetch;
	//		++i_sub;
	//	}
	//	else	///从next数组获取回退位置
	//	{
	//		i_sub = next[i_sub];
	//		//++i_fetch;
	//	}
	//}
	//if (i_sub > Sub_String.length)
	//	return i_fetch - Sub_String.length + 1;
	//else
	//	return -1;

	int* pmt = new int[Sub_String.length];
	for (int i = 0; i < Sub_String.length; ++i)
	{
		for (int length_match = i; length_match >= 1; --length_match)
		{
			bool found = true;
			for (int k = 0; k < length_match; ++k)
			{
				if (Sub_String.string_[k] != Sub_String.string_[i - length_match + k + 1])
				{
					found = false;
					break;
				}
			}

			if (found)
			{
				pmt[i] = length_match;
				break;
			}
		}
	}

	int i_fetch = 0;
	int i_sub = 0;
	
}




