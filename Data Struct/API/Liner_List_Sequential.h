#pragma once

typedef int DataType;

struct SequentialList
{
	DataType* data;
	int length;	//当前表长
	int maxsize;
};
typedef struct SequentialList SeqList;
//创建有maxsize个元素空间的顺序表，返回表首地址
//所有元素值初始化为0
SeqList* SeqList_Init(int maxsize);	
//销毁线性顺序表
void SeqList_Destroy(SeqList* List);	
//在线性顺序表List第pos个位置插入元素值data
void SeqList_Insert(SeqList* List, int pos, DataType data);	
//删除链表List第pos个位置上的元素，返回元素值
DataType SeqList_Delete(SeqList* List, int pos);
//修改链表List第pos个位置上的元素值为data
void SeqList_Update(SeqList* List, int pos, DataType data);
//显示顺序表List元素空间上的所有元素
void SeqList_Show(SeqList* List);







