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

//顶点节点
struct AdjacencyList_Vertex
{
	int no;//顶点在邻接表中的下标
	std::string name;//顶点名
	DataType* data;//数据元素
	Edge_Adj* head_edge;//存放边信息
};
typedef struct AdjacencyList_Vertex Vertex_AdjacencyList;

//邻接表
struct AdjacencyList
{
	bool directed;
	int num_vertex;
	int num_edge;
	bool* state_visited;//访问状态
	AdjacencyList_Vertex* vertex;//顶点数组
};
typedef struct AdjacencyList AdjacencyList;

//显示邻接表
void Graph_Show_AdjacencyList(AdjacencyList* graph);

static void Reset_VistedState(AdjacencyList* graph)
{
	for (int i = 0; i < graph->num_vertex; i++)
		graph->state_visited[i] = false;
}

//初始化邻接表空间
void Graph_AdjacencyList_Init(AdjacencyList* graph, int num_vertex, bool directed);
//添加图graph中，从x到y的边，权值为weight
void Graph_AdjacencyList_Edge_Add(AdjacencyList* graph, int no_origin, int no_destination, int weight);

//广度优先遍历
void Graph_AdjacencyList_Traverse_DFS(AdjacencyList* graph, int no_vertex);


//深度优先遍历
void Graph_AdjacencyList_Traverse_BFS(AdjacencyList* graph, int no_vertex);
