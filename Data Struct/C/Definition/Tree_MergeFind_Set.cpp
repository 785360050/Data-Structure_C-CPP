#include <iostream>

#include "../API/Tree_MergeFind_Set.h"
#include "../API/Liner_Stack.h"
///————————————————————————————————————————————————————————————————————
///QuickFind
MFSet_QuickFind* Set_Create_QuickFind(int n)
{///分配头节点和组ID空间
	MFSet_QuickFind* set = new MFSet_QuickFind;
	set->n = n;//元素个数
	set->data = new DataType[n];
	set->ID = new int[n];
	return set;
}

void Set_Destroy(MFSet_QuickFind* set)
{
	if (set)
	{
		if (set->data)
			delete[] set->data;
		if (set->ID)
			delete[] set->ID;
	}
	delete set;
}

void Set_Init(MFSet_QuickFind* set, const DataType* data, int n)
{
	for (int i = 0; i < n; i++)
	{///根据
		/// <summary>
		/// 初始化数据元素组ID=元素值本身
		/// </summary>
		/// <param name="set"></param>
		/// <param name="data"></param>
		/// <param name="n"></param>
		set->data[i] = data[i];
		set->ID[i] = i;
	}
}

//获取元素对应的索引(组ID)
static int Index(MFSet_QuickFind* set, DataType x)
{
	for (int i = 0; i < set->n; ++i)
		if (set->data[i] == x)
			return i;
	return -1;//找不到则返回失败
}
bool Find(MFSet_QuickFind* set, DataType x, DataType y)
{
	int Index_X = Index(set, x);
	int Index_Y = Index(set, y);
	if (Index_X == -1 || Index_Y == -1)
		return false;//任意查找索引失败返回失败
	if (set->ID[Index_X] == set->ID[Index_Y])//返回成功
		return true;
	else
		return false;
}

void Merge(MFSet_QuickFind* set, DataType x, DataType y)
{
	int Index_X = Index(set, x);
	int Index_Y = Index(set, y);
	int ID_X = set->ID[Index_X];
	int ID_Y = set->ID[Index_Y];
	for (int i = 0; i < set->n; ++i)
		if (set->ID[i] == ID_X)///遍历寻找x的组ID，设置为Y的组ID，完成合并
			set->ID[i] = ID_Y;

}

void Set_Show(const MFSet_QuickFind* const set)
{
	std::cout << "[data:ID]" << std::endl;
	for (int i = 0; i < set->n; i++)
	{
		std::cout << '[' << set->data[i] << ':' << set->ID[i] << "],";
	}
	std::cout << std::endl;
}


///————————————————————————————————————————————————————————————————————
///QuickMerge
MFSet_QuickMerge* Set_Create_QuickMerge(int n)
{
	MFSet_QuickMerge* set = new MFSet_QuickMerge;
	set->data = new DataType[n];
	set->parents = new int[n];
	set->size = new int[n];
	set->n = n;
	return set;
}

void Set_Destroy(MFSet_QuickMerge* set)
{
	if (set)
	{
		if (set->size)
			delete set->size;
		if (set->parents)
			delete set->parents;
		if (set->data)
			delete[] set->data;
		delete set;
	}
}

void Set_Show(const MFSet_QuickMerge* const set)
{
	std::cout << "[Element data : Parent ID : Group Size]" << std::endl;
	for (int i = 0; i < set->n; i++)
	{
		std::cout << '[' 
			<< set->data[i] << ':' 
			<< set->parents[i] << ':' 
			<<set->size[i] << "],";
	}
	std::cout << std::endl;
}

void Set_Init(MFSet_QuickMerge* set, const DataType* data, int n)
{
	for (int i = 0; i < n; ++i)
	{
		set->data[i] = data[i];
		set->parents[i] = i;
		set->size[i] = 1;
	}
}
//寻找元素值为data的元素的下标索引
static int Index(MFSet_QuickMerge* set, DataType data)
{///遍历找值为data的元素，返回该元素下标
	/// <summary>
	/// 循环遍历寻找值为data的元素的双亲parents,
	/// 直到找到双亲ID==自己ID的节点，即为data元素所在集合的RootID
	/// 返回根节点ID，失败返回-1
	/// </summary>
	/// <param name="set"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	for (int i = 0; i < set->n; ++i)
		if (set->data[i] == data)
			return i;
	return -1;
}
//遍历寻找元素data所在的集合(根)ID
int RootIndex(MFSet_QuickMerge* set, DataType data)
{
	int temp = Index(set, data);
	if (temp == -1)
		return -1;
	///找根(双亲为自己即为根)
	while (set->parents[temp] != temp)
		temp = set->parents[temp];//向上移动
	return temp;//返回根ID
}
//遍历寻找元素data所在的集合(根)ID
//路径压缩
int RootIndex_Optimized(MFSet_QuickMerge* set, DataType data)
{///利用栈实现路径压缩
	int temp = Index(set, data);
	if (temp == -1)
		return -1;
	SeqStack* path = SeqStack_Init(10);
	while (set->parents[temp] != temp)
	{
		SeqStack_Push(path, temp);//将路径的下标索引入栈
		temp = set->parents[temp];
	}
	while (path->top>0)
	{
		int pos = SeqStack_Pop(path);
		set->parents[pos] = temp;
	}
	SeqStack_Destroy(path);
	return temp;
}

bool Find(MFSet_QuickMerge* set, DataType x, DataType y)
{
	int RootID_X = RootIndex(set, x);
	int RootID_Y = RootIndex(set, y);
	try
	{
		if (RootID_X == -1 || RootID_Y == -1)
			throw 1;
	}
	catch (...)
	{
		std::cout << "查找失败，元素所在集合的RootID不存在" << std::endl;
		return false;
	}
	if (RootID_X == RootID_Y)
		return true;//所在集合的根ID一致时返回true
	else
		return false;
}

void Merge(MFSet_QuickMerge* set, DataType x, DataType y)
{
	/// <summary>
	/// 通过修改集合的RootID的合并两个元素
	/// 将数量小的集合的根元素的parent修改为数量多的集合的根的下标
	/// </summary>
	/// <param name="set"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	int RootID_X = RootIndex(set, x);
	int RootID_Y = RootIndex(set, y);
	if (RootID_X == -1 || RootID_Y == -1)
	{
		std::cout << "合并失败" << std::endl;
		return;
	}
	if (RootID_X != RootID_Y)
	{///不在同一个集合时才合并
		int Size_X = set->size[RootID_X];
		int Size_Y = set->size[RootID_Y];
		if (Size_X >= Size_Y)
		{///元素少的集合合并到大的集合
			set->parents[RootID_Y] = RootID_X;//小的集合的根节点双亲改为大集合的根节点下标
			set->size[RootID_X] += Size_Y;//更新大的集合子节点个数
		}
		else
		{
			set->parents[RootID_X] = RootID_Y;
			set->size[RootID_Y] += Size_X;
		}

	}
}



