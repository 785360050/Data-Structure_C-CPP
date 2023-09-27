#pragma once

#include "Global Variables.h"

/*
* ///2种实现
1.Quick Find		利用顺序存储实现
	查找效率：O(1)
	合并效率：O(N)
2.Quick Union		利用链式存储实现
	查找效率：O(logN)
	合并效率：O(logN)
*/
#define Quick_Find
#define Quick_Merge

#ifdef Quick_Find

struct MergeFind_Set_QuickFind
{
	DataType* data;//元素集合
	int* ID;//集合中元素对应的组ID
	int n;//集合中元素个数
};
typedef struct MergeFind_Set_QuickFind MFSet_QuickFind;

//初始化查并集头节点
MFSet_QuickFind* Set_Create_QuickFind(int n);
//释放查并集空间
void Set_Destroy(MFSet_QuickFind* set);
//显示整个查并集
void Set_Show(const MFSet_QuickFind* const set);
//初始化查并集
//将元素集合存放再顺序数组data中，ID数组存放每个元素对应的组ID
void Set_Init(MFSet_QuickFind* set, const DataType* data, int n);
//判断查并集set中，元素x,y是否再同一个集合中
//O(1)
bool Find(MFSet_QuickFind* set, DataType x, DataType y);
//合并查并集set中元素x,y到同一集合中(x加入y的组)
//O(n)
void Merge(MFSet_QuickFind* set, DataType x, DataType y);

#endif // QuickFind

#ifdef Quick_Merge

struct MergeFind_Set_QuickMerge
{
	DataType* data;//元素集合
	int* parents;//存放双亲的ID
	int* size;//记录所在集合的元素总数(包含的子节点个数，仅在根节点合并时使用)
	int n;//集合元素数量(用于分配数组元素个数)
};
typedef MergeFind_Set_QuickMerge MFSet_QuickMerge;

//初始化查并集头节点，各自申请n个大小的数组空间
MFSet_QuickMerge* Set_Create_QuickMerge(int n);
//释放查并集空间
void Set_Destroy(MFSet_QuickMerge* set);
//显示整个查并集
void Set_Show(const MFSet_QuickMerge* const set);
//初始化查并集
//将n个元素依次存放在顺序数组data中
//元素对应双亲的索引存放在parents数组中
//(初始双亲为自己，即根ID=双亲ID=元素数组下标)
//初始化每个集合中元素个数为1
void Set_Init(MFSet_QuickMerge* set, const DataType* data, int n);
//判断查并集set中，元素x,y是否再同一个集合中
//O(logN) 
bool Find(MFSet_QuickMerge* set, DataType x, DataType y);
//合并查并集set中元素x,y到同一集合中
//O(logN)
void Merge(MFSet_QuickMerge* set, DataType x, DataType y);

int RootIndex(MFSet_QuickMerge* set, DataType data);
int RootIndex_Optimized(MFSet_QuickMerge* set, DataType data);


#endif // Quick_Union




