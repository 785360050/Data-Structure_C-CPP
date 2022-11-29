#pragma once

#include <iostream> 

/// 从1开始存储，第一个空间不使用
struct String
{
	char* string_;	///0开始计数
	int length;
};

//初始化
void String_Init(String& string, const char* cha);

//销毁
void String_Destroy(String& string);

//朴素匹配算法(返回下标,失败返回-1)
int String_Fetch_Brute_Force(const String& string, const String& Sub_String);

//KMP匹配算法(返回下标,失败返回-1)
int String_Fetch_KMP(const String& string, const String& Sub_String);







