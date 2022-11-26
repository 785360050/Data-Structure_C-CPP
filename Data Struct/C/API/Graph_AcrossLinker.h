#pragma once

#include "Global Variables.h"
#include <iostream>


struct AcrossList_Edge
{
	int weight;
	struct AcrossList_Edge* next_tail;
	int Arc_Tail;//弧头
	int Arc_Head;//弧尾
};
typedef struct AcrossList_Edge Edge_AcrossList;

struct AcrossList_Vertex
{
	int index;
	std::string name;
	AcrossList_Edge* Head_In;//入度链表
	AcrossList_Edge* Head_Out;//出度链表
	DataType data;
};
typedef struct AcrossList_Vertex Vertex_AcrossList;

struct AcrossList
{
	//AcrossList_Vertex[maxsize];
	int num_node;
	int num_edge;
};

