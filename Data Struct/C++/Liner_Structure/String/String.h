#pragma once

#include <iostream> 
#include <string>

/// 从1开始存储，第一个空间不使用
class String
{
public:
	char* string_;	///0开始计数,字符串数组
	int length;
public:
    char& operator[](int i) const
    {//重载运算符[]
        return string_[i];
    }
public:
//初始化
	String(const char* string):length(strlen(string))
	{
		if (!string)
			throw std::exception("String is nullptr");

		if (string_)
			delete[] string_;

		string_ = new char[length + 1];///字符+'\0'
		for (int i = 0; i < length +1; ++i)
			string_[i] = string[i];
	}

	~String()
	{
		if (string_)
			delete[] string_;
	}
};


////朴素匹配算法(返回下标,失败返回-1)
//int String_Fetch_Brute_Force(const String& string, const String& Sub_String);
//


///KMP匹配算法(返回下标,失败返回-1)
/// 实现前提
/// 1.next数组此处等价于Prefix前缀表，未加工处理(如右移或全部加1)
/// 遇到不匹配字符时，找next数组对应元素的前一位，确定回退的位置(下标)
int* Prefix_Array(const String& s)
{ /// 生成并返回前缀表next数组
    int* next = new int[s.length];
    int prefix_end = 0;                                           // 同时也是最长相同前后缀的长度
    next[0] = 0;                                                  // 初始位置为0，非-1
    for (int suffix_end = 1; suffix_end < s.length; suffix_end++) // 因为单字符必为0，所以从1开始(长度2)计算最长相同前后缀
    {                                                             // 后缀末尾从1开始(后缀不包含首元素)，计算最长相同前后缀不是用字符串比较，而是遍历计数
        // 前后缀不同时
        while (prefix_end > 0 && s[suffix_end] != s[prefix_end]) // 无相同前后缀时，后缀末尾收缩(向右回退)，prefix_end > 0控制回退的终点限制
            prefix_end = next[prefix_end - 1];                   // 通过查前一位的next数组中元素的值，确定回退的位置(难)
        // 字符相同时，匹配
        if (s[suffix_end] == s[prefix_end])
            prefix_end++;


        // 更新next数组
        next[suffix_end] = prefix_end;
    }
    return next;
}
///用KMP算法查找Sub_String在string中的匹配的下标位置，不存在时返回-1下标
int String_Fetch_KMP(const String& string, const String& Sub_String)
{ /// 有点动态规划的味道，KMP相比朴素比较算法可以减少相同子串重复比较的次数
    if (Sub_String.length == 0)
        return 0;

    int* next = Prefix_Array(Sub_String); // 初始化next数组
    for (int i = 0; i < Sub_String.length; ++i)
        std::cout << next[i] << ' ';
    std::cout << std::endl;

    for (int i = 0, j = 0; i < string.length; i++)
    { // 利用next数组(前缀表)，在遍历的时候匹配
        while (j > 0 && string[i] != Sub_String[j])
            j = next[j - 1]; // 找前缀表中相应元素的前一个元素值(最长相同前后缀)
        if (string[i] == Sub_String[j]) // 字符相同时
            j++;

        if (j == Sub_String.length)
            return (i - Sub_String.length + 1);
    }
    return -1;
}











