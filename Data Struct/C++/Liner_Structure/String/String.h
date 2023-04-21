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
public://初始化

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
private:///KMP函数
    // 查前缀表，获取匹配失败时回退到的下标位置
    int Index_Get(int* prefix_array, int index) const
    {
        return prefix_array[index - 1];
    }

    // 生成并返回子串的前缀表next数组(此处等价于prefix数组，未作处理)
    int* Prefix_Array(const String& s)
    {
        int* prefix = new int[s.length];
        prefix[0] = 0; // 单个字符不可能有匹配的前后缀

        // 跳过单个字符的处理
        // end_suffix同时也是最长相同前后缀的个数,作为结果存入next数组
        for (int end_suffix = 1, end_prefix = 0; end_suffix < s.length; ++end_suffix)
        { // 每轮找到最长的相同前后缀长度

            /// 字符不同，匹配失败，前缀回退
            while (end_prefix > 0 && s[end_prefix] != s[end_suffix])
                end_prefix = Index_Get(prefix, end_prefix); // 查next数组中的回退位置

            /// 字符相同，匹配成功，前缀增加(前缀增加也代表相同前后缀的长度增加)
            if (s[end_prefix] == s[end_suffix])
                end_prefix++; // 最长相等前后缀的长度+1，同时向后查找更长的相同前后缀长度

            /// 已得到本轮最长相同前后缀的长度，更新到next数组
            prefix[end_suffix] = end_prefix;
        }

        return prefix;
    }
public:
    // 实现前提
       // 1.next数组此处等价于Prefix前缀表，未加工处理(如右移或全部加1)
       // 遇到不匹配字符时，找next数组对应元素的前一位，确定回退的位置(下标)
    // 注：不能调整前后缀判定顺序，此处时先判定不同，再判定相同，否则会出错(可能需要修改才行)
    int String_Fetch_KMP(const String& Substring)
    {
        if (Substring.length == 0)
            return 0;

        // next数组存放最长相同的前后缀长度，
        //  若发生失配，则回退到，next数组中对应最长前后缀长度的下一个位置(也就是避免重复匹配)
        int* next = Prefix_Array(Substring); // 初始化next数组
        /// 显示next数组
        for (int i = 0; i < Substring.length; ++i)
            std::cout << next[i] << ' ';
        std::cout << std::endl;

        // 遍历主串，找目标子串
        for (int i_main = 0, i_sub = 0; i_main < this->length; ++i_main)
        {
            // 失配：查找next数组中前一个位置的元素值(回退到的目的下标)
            while (i_sub > 0 && this->string_[i_main] != Substring[i_sub])
                i_sub = Index_Get(next, i_sub);

            // 成功配对字符：匹配下一个字符
            if (this->string_[i_main] == Substring[i_sub])
                ++i_sub;

            // 全部匹配完成
            if (i_sub == Substring.length)
                // 当前主串匹配位置(成功匹配子串的末尾字符)-子串长度+1(转到第一个成功匹配子串的字符)
                return (i_main - Substring.length + 1);
        }
        return -1; // 匹配失败，返回-1
    }
public:
    ////朴素匹配算法(返回下标,失败返回-1)
    int String_Fetch_Brute_Force(const String& Sub_String)
    {
        if (this->length < Sub_String.length)
            return -1;
        int i_fetch = 0;
        for (; i_fetch <= length; ++i_fetch)
        {
            int i_sub = 0;
            for (; i_sub < Sub_String.length; ++i_sub)
                if (this->string_[i_fetch + i_sub]!=Sub_String[i_sub])
                    break;
            if (i_sub >= Sub_String.length)
                return i_fetch;
        }
        return -1;
    }
};
















