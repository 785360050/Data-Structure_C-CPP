//#include <iostream>
//#include "../API/Graph_EdgeSetList.h"
//#include <stack>
//
//
//void Graph_EdgeSetList_Init(Graph_EdgeSet* graph, int num_vertex, bool directed)
//{
//	graph->num_vertex = num_vertex;
//	graph->num_edge = 0;
//	graph->directed = directed;
//	graph->vertex = new int[num_vertex];
//	graph->edge = new std::stack<Graph_EdgeSet_Edge>;///n个顶点最多有n(n-1)条边
//}
//
//
////释放邻接矩阵空间
//void Graph_EdgeSetList_Destroy(Graph_EdgeSet* graph)
//{
//	try
//	{
//		if (!graph)
//			throw 1;
//	}
//	catch (...)
//	{
//		std::cout << "Graph Destroyed Failed: Graph is not exisit!" << std::endl;
//		return;
//	}
//	delete[] graph->edge;
//	delete[] graph->vertex;
//	delete graph;
//}
////添加边(已存在时不添加)
//void Graph_EdgeSetList_Edge_Add(Graph_EdgeSet* graph, int no_origin, int no_destination, int weight)
//{
//	try
//	{
//		if (!graph)
//			throw 1;
//	}
//	catch (...)
//	{
//		std::cout << "Graph Destroyed Failed: Graph is not exisit!" << std::endl;
//		return;
//	}
//	///边集数组的添加、删除边，不必满足有序，连续
//	///栈存储
//
//	Graph_EdgeSet_Edge e;
//	e.no_destination = no_destination;
//	e.no_source = no_origin;
//	e.weight = weight;
//	graph->edge->push(e);
//
//	
//}
//
//
//
//
//
