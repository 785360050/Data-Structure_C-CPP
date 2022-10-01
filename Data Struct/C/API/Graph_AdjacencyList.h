#pragma once

#include <iostream>
#include "Global Variables.h"

struct AdjacencyList_Edge
{
	int index_vertex;//顶点的下标索引
	int weight;//边权重
	struct AdjacencyList_Edge* next;
};
typedef struct AdjacencyList_Edge Edge_Adj;//邻接表的边(弧)

struct AdjacencyList_Vertex
{
	int index;
	std::string name;
	DataType* data;
	Edge_Adj* head;
};
typedef struct AdjacencyList_Vertex Vertex_AdjacencyList;

struct AdjacencyList
{
	Vertex_AdjacencyList vertex[maxsize];
	int num_vertex;
	int num_edge;
	bool directed;
};
typedef struct AdjacencyList AdjacencyList;


//初始化邻接表空间
void Graph_AdjacencyList_Init(AdjacencyList* graph, int num_vertex, bool directed);
//添加图graph中，从x到y的边，权值为weight
void Graph_AdjacencyList_Edge_Add(AdjacencyList* graph, int x, int y, int weight);


