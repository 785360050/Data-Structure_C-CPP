#pragma once


struct Graph_EdgeSet_Edge
{
	int no_source;
	int no_destination;
	int weight;
};
typedef struct Graph_EdgeSet_Edge Graph_EdgeSet_Edge;

struct Graph_EdgeSet
{
	int count;
	bool directed;
	int* vertex;//存放顶点的数组
	Graph_EdgeSet_Edge* edge;//存放边的数组
};
typedef struct Graph_EdgeSet Graph_EdgeSet;


//初始化边集数组
void Graph_EdgeSetList_Init(Graph_EdgeSet* graph, int num_vertex, bool directed);

//释放邻接矩阵空间
void Graph_EdgeSetList_Destroy(Graph_EdgeSet* graph);
//添加边(已存在时不添加)
void Graph_EdgeSetList_Edge_Add(Graph_EdgeSet* graph, int no_origin, int no_destination, int weight);

















