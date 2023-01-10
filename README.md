# Executable Data-Structure Code for C/C++
## Introduction
> Hi there! This is Jevon 
> - I'm new to all these thing including 
>  **GitHub ,   Data Struct ,   Coding Language C and C++**  
> * Since it's the second time for me to study Data Struct,
I consider it a good time to code runnable code with C and C++.
The reference book i use is **《Data Dtructure》 written by 严蔚敏**
>
>* I've met huge difficulties when I first studying this book, 
which provide massive pseudocode. I can only try to understand the code 
in book without typing them in IDE to verify them. 
>* Then this project occured to solve that obstacle, 
**You can immediately use some parts or modify little codes to prove your thoughts**.
- tips:
It's a normalized coding style project that might be mied by c++ grammer in C programe 


## Guide
### Using Tool: Visual Studio 2022

Files in Github 
> Non Visual Studio Users can get started by main.cpp and C or C++  

|File/Folder name | describtion|Path|
|:-:|:-:|:-:|
|C| C style codes with c++ |Data Struct/C |
|C++| C++ codes with features such as template |Data Struct/C++|
|Alogorithm|Part of sort and search method|Data Struct/Alogorithm|
|API| Declarations of Storage srtuctures |Annotations help you call functions|
|Definition|Definitions for API |Specific codes how function runs
|main.cpp|**Test Codes for C/C++** |Data Struct/main.cpp|
|Data Struct.sln| **VS Enterance** |/|


##  `Details`
- [Test Case](#test-case)
- [Class Diagram](#class-diagram)
- [Structure Storage](#memory-structure)


## main.cpp
>    you can control wheather C or C++ Data Structure test codes by #define C/CPP
>    example:
```C++
#define C
//#define CPP

#ifdef C
...
#endif // C

#ifdef CPP
...
#endif // CPP


#include <Windows.h>
///修改cmd编码方式
static bool  SetEncode(int EncodeId = 936)

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	
	Test_C();
	//Test_CPP();

}
```
>   - Select the Data structure function by remove "//"

## Attention!
- C Project is aim to work correctly when CPP Project is aim to clear up all these Structures.
- //完毕 only refers functions are basically tested, it may well be something wrong when modifying them.
- So I reccommend you commit in issues , even commit updates.
- Hope it helps your study :D


#### Basic Knowledege
* baisc print function in **C** is printf while I used std::cout in **C++** instead all the times
>C++
> ```C
> void main()
> {
>     int x;
>     std::cin >> x;//输入
>     std::cout << x << std::endl;//输出
>     return 1
> }
> ```
> also you can use namespace std to remove **std::**
> ```C++
> using namespace std;
> int main()
> {
>     int x;
>     cin >> x;//输入
>     cout << x << endl;//输出
>     return 1
> }
> ```
>> **If you want appoint C as your coding language you should craete .c files rather than .cpp files which Visual Studio always make .cpp file for c++**

#### High quality Website
[Runnoob](http://www.runoob.com/) is good enough for who unfamiliar with coding gramma.  
[Data Structure Visualization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html) helped me a lot in [Black-Red Tree](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

# In Progress
- Developing C++ codes by using Object-Oriented
- Memory Digrames for each structure.
- Digrames storage by Edge-Set
- Using namespace instead of long function name in CPP project



# Test Case
## Binary Tree
![二叉树遍历示例树](https://i.imgur.com/mOViysT.png)

## Binary Search Tree
![二叉搜索树案例](https://i.imgur.com/pMzjRuA.png)

## Topo Sort
![Structure-拓扑排序.drawio](https://i.imgur.com/OHTsjvZ.png)

## Critical Path
![关键路径](https://i.imgur.com/0Wi2hWb.png)

## Minimum Spanning Tree
![Structure-最小生成树.drawio](https://i.imgur.com/6pV2ZNP.png)

## Black-Red Tree
![Structure-红黑树.drawio](https://i.imgur.com/EucN0tf.png)
---
# Memory Structure
## Sequentence List
![顺序表](https://i.imgur.com/lOkHXih.png)



# Class Diagram
![Liner_Structure](https://i.imgur.com/SzzrtU3.png)

# [Top](#executable-data-structure-code-for-cc)



