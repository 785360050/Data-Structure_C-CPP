#include <iostream>
#include "../API/Graph_EdgeSetList.h"



void Graph_EdgeSetList_Init(Graph_EdgeSet* graph, int num_vertex, bool directed)
{
	graph->num_vertex = num_vertex;
	graph->num_edge = 0;
	graph->directed = directed;
	graph->vertex = new int[num_vertex];
	graph->edge = new Graph_EdgeSet_Edge[num_vertex * (num_vertex - 1)];///n个顶点最多有n(n-1)条边
}


//释放边集数组空间
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
{///无向图仅储存两个记录
	try
	{
		if (!graph)
			throw std::exception("Graph Edge Add Failed: Graph is not exisit!");
		for (int i = 0; i < graph->num_edge; ++i)
		{
			if (graph->edge->no_source == no_origin && graph->edge->no_destination == no_destination)
				throw std::exception("Graph Edge Add Failed : Edge already exisited!");
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}
	///边集数组的添加、删除边，不必满足有序，连续
	
	graph->edge[graph->num_edge].no_source = no_origin;
	graph->edge[graph->num_edge].no_destination = no_destination;
	graph->edge[graph->num_edge].weight = weight;
	++graph->num_edge;
	if (graph->directed == false)
	{
		graph->edge[graph->num_edge].no_source = no_destination;
		graph->edge[graph->num_edge].no_destination = no_origin;
		graph->edge[graph->num_edge].weight = weight;
		++graph->num_edge;
	}
	
}

void Graph_EdgeSetList_Edge_Delete(Graph_EdgeSet* graph, int no_origin, int no_destination)
{
	//try
	//{
	//	for (int i = 0; i < graph->num_edge; ++i)
	//	{
	//		if (graph->edge[i].no_source == no_origin && graph->edge[i].no_destination == no_destination)
	//			throw std::exception("Edge Delete Failed: Edge is not exist!");
	//	}
	//}
	//catch (const std::exception& e)
	//{
	//	std::cout << e.what() << std::endl;
	//	return;
	//}
	//int num_edge = graph->num_edge;
	//if (!graph->directed)
	//	num_edge /= 2;
	for (int i = 0; i < graph->num_edge; ++i)
	{
		if (graph->edge[i].no_source == no_origin && graph->edge[i].no_destination == no_destination)
		{
			for (int p = i; p < graph->num_edge; ++p)
				graph->edge[p] = graph->edge[p + 1];
			--graph->num_edge;
			graph->edge[graph->num_edge - 1].no_source = NULL;
			graph->edge[graph->num_edge - 1].no_destination = NULL;
			graph->edge[graph->num_edge - 1].weight = NULL;

			if (graph->directed == false)
				Graph_EdgeSetList_Edge_Delete(graph, no_destination, no_origin);
			return;
		}
	}
}

void Graph_EdgeSetList_Show(const Graph_EdgeSet* const graph)
{
	int num_edge = graph->num_edge;
	if (!graph->directed)
		num_edge /= 2;
	std::cout << (graph->directed ? "有向图" : "无向图") << std::endl;
	std::cout << " [顶点数 : 边数] " << graph->num_vertex << ':' << num_edge << std::endl;
	std::cout << "index [source:destination:weight]" << std::endl;
	for (int i = 0; i < graph->num_edge; ++i)
		std::cout << i << " [" 
		<< graph->edge[i].no_source << ':' 
		<< graph->edge[i].no_destination << ':'
		<< graph->edge[i].weight << ']' << std::endl;

}

