#include <iostream>
#include "../API/Graph_EdgeSetList.h"



void Graph_EdgeSetList_Init(Graph_EdgeSet* graph, int num_vertex, bool directed)
{
	graph->count = num_vertex;
	graph->directed = directed;
	graph->vertex = new int[num_vertex];
	graph->edge = new Graph_EdgeSet_Edge[(num_vertex)*(num_vertex-1)];///n个顶点最多有n(n-1)条边
	memset(graph->edge, 0, sizeof(Graph_EdgeSet_Edge) * num_vertex);
}


//释放邻接矩阵空间
void Graph_EdgeSetList_Destroy(Graph_EdgeSet* graph)
{
	try
	{
		if (!graph)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Graph Destroyed Failed: Graph is not exisit!" << std::endl;
		return;
	}
	delete[] graph->edge;
	delete[] graph->vertex;
	delete graph;
}
//添加边(已存在时不添加)
void Graph_EdgeSetList_Edge_Add(Graph_EdgeSet* graph, int no_origin, int no_destination, int weight)
{
	try
	{
		if (!graph)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Graph Destroyed Failed: Graph is not exisit!" << std::endl;
		return;
	}
	///边集数组的添加、删除边，不必满足有序，连续
}




