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
> Non Visual Studio Users can take Source Files in C or C++ Folder

|File/Folder name | describtion|Path|
|:-:|:-:|:-:|
|C| C style codes with c++ |Data Struct/C |
|C++| C++ codes with features such as template |Data Struct/C++|
|Alogorithm|Part of sort and search method|Data Struct/Alogorithm|
|API| Declarations of Storage srtuctures |Data Struct/C/API|
|Definition|Definitions for API |Data Struct/C/Definition
|main.cpp|**Test Codes for C/C++** |Data Struct/main.cpp|
|Structure.drawio|Structure Diagram for Test Cases|/res
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

### Test Sample Demo in C++ with polymorphic
#### Link_List
```C++
void Test_LinkList()
{

	Liner_List<List_Node_SingleWay<int>, int>* link_list = new Link_List_Forward<int>;

	link_list->List_Show("Initialize");

	for (int i = 1; i <= 5; i++)
		link_list->Element_Insert(i, i);
	link_list->List_Show("插入5个元素后");


	link_list->Element_Insert(2, 9);
	link_list->List_Show("第二个位置插入9后，链表扩展一个元素");

	std::cout << std::endl;
	link_list->Element_Insert(20, 20);
	link_list->List_Show("第20个非法位置插入20后");

	std::cout << std::endl;
	link_list->Element_Update(2, 999);
	link_list->List_Show("第二个元素改为999后");

	int del = link_list->Element_Delete(2);
	link_list->List_Show("删除第二个元素后");
	std::cout << "删除的第二个元素为:" << del << std::endl;

	std::cout << "获取第二个元素值:" << link_list->List_GetData(2) << std::endl;

	std::cout << "判空:" << std::boolalpha << link_list->List_CheckEmpty() << std::endl;
	std::cout << "当前表长：" << link_list->List_GetLength() << std::endl;
	link_list->List_Clear();
	link_list->List_Show("元素重置后");
	std::cout << "当前表长：" << link_list->List_GetLength() << std::endl;

	delete link_list;
}
```
![Screenshot 2023-02-01 170242](https://i.imgur.com/yjRAXND.jpg)
#### Graph in Matrix
```C++
void TestPolymorphic()
{
	Graph_Structure<Vertex_Matrix<int>,int>* graph=new Graph_Matrix<int>(true, 7);

	graph->Graph_Edge_Add(0, 1, 4);
	graph->Graph_Edge_Add(0, 2, 6);
	graph->Graph_Edge_Add(0, 3, 6);
	graph->Graph_Edge_Add(1, 2, 1);
	graph->Graph_Edge_Add(1, 4, 7);
	graph->Graph_Edge_Add(2, 4, 6);
	graph->Graph_Edge_Add(2, 5, 4);
	graph->Graph_Edge_Add(3, 2, 2);
	graph->Graph_Edge_Add(3, 5, 5);
	graph->Graph_Edge_Add(4, 6, 6);
	graph->Graph_Edge_Add(5, 4, 1);
	graph->Graph_Edge_Add(5, 6, 8);

	graph->Graph_Show();

	std::cout << "DFS" << std::endl;
	graph->Graph_Traverse_DFS(0);
	std::cout << std::endl << "BFS" << std::endl;
	graph->Graph_Traverse_BFS(0);

	delete graph;
}
```
![Screenshot 2023-02-01 170409](https://i.imgur.com/eoSTCnB.jpg)
## Attention!
- C Project is aim to work correctly when CPP Project is aim to clear up all these Structures.
- //完毕 only refers functions are basically tested, it may well be something wrong when modifying them.
- So I reccommend you commit in issues , even commit updates.
- Hope it helps your study :D


#### Basic Knowledege
* baisc print function in **C** is printf while I used std::cout in **C++** instead all the times

> **If you want appoint C as your coding language you should craete .c files rather than .cpp files which Visual Studio always make .cpp file for c++**

#### High quality Website
[Runnoob](http://www.runoob.com/) is good enough for who unfamiliar with coding gramma.  
[Data Structure Visualization](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html) helped me a lot in [Black-Red Tree](https://www.cs.usfca.edu/~galles/visualization/RedBlack.html)

# In Progress
- Developing C++ codes by using Object-Oriented
- Still thinking about how to combine Algorithms with classes
- Using namespace instead of long function name in CPP project
- ***NEED MORE TEST CASE***
- B+ Tree Delete is not Implemented, need some help


# Test Case
## Binary Tree
![二叉树遍历示例树](https://i.imgur.com/mOViysT.png)

## Binary Search Tree
![二叉搜索树案例](https://i.imgur.com/pMzjRuA.png)

## Graph 
![Structure-图.drawio](https://i.imgur.com/2lfMCxA.png)

## Topo Sort
![Structure-拓扑排序.drawio](https://i.imgur.com/OHTsjvZ.png)

## Critical Path
![关键路径](https://i.imgur.com/0Wi2hWb.png)

## Minimum Spanning Tree
![Structure-最小生成树.drawio](https://i.imgur.com/6pV2ZNP.png)

## Black-Red Tree
![Structure-红黑树.drawio](https://i.imgur.com/EucN0tf.png)

## B Tree(5 Order with 4 elements)
![B_Tree](https://i.imgur.com/YmqNfJk.png)

---
# Memory Structure
## Sequentence List
![顺序表](https://i.imgur.com/lOkHXih.png)



# Class Diagram
## Liner_Structur
### Liner_List
![Liner_List](https://i.imgur.com/3qB3G1w.png)

### Liner_Queue
![Liner_Queue](https://i.imgur.com/8pwLjS8.png)

### Liner_Stack
![Liner_Stack](https://i.imgur.com/uuTEcJl.png)

## Tree_Structur
### Tree_Heap
![Heap](https://i.imgur.com/7Vi1W5z.png)
### Tree_MergeFindSet
![MergeFindSet](https://i.imgur.com/c1xeRQn.png)
### Tree
![Tree](https://i.imgur.com/MDHHLDW.png)
#### Binary Tree
![Binary_Tree.drawio](https://i.imgur.com/fsU1xHP.png)
##### Binary_Search_Tree
![Binary Search Tree](https://i.imgur.com/1JoO5GQ.png)
#### HighOrder_Tree
![HighOrder Tree](https://i.imgur.com/15Rmynm.png)
##### Tree_Normal
![Tree_Normal](https://i.imgur.com/3XT7sdD.png)
##### Tree_B
![Tree_B](https://i.imgur.com/SW1Mp1H.png)

## Link Node
![Node](https://i.imgur.com/1bKdU8f.png)



# [Top](#executable-data-structure-code-for-cc)



