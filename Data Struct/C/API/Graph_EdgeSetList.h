//#pragma once
//
//#include "Graph_matrix.h"
/////TODO Unfinished
//struct Graph_EdgeSet_Edge
//{
//	int no_source;
//	int no_destination;
//	int weight;
//};
//typedef struct Graph_EdgeSet_Edge Graph_EdgeSet_Edge;
//
//struct Graph_EdgeSet
//{
//	bool directed;
//	int num_vertex;
//	int num_edge;
//	int* vertex;//存放顶点的数组
//	std::stack<Graph_EdgeSet_Edge>* edge;//存放边的数组(栈实现)
//};
//typedef struct Graph_EdgeSet Graph_EdgeSet;
//
//
////初始化边集数组
//void Graph_EdgeSetList_Init(Graph_EdgeSet* graph, int num_vertex, bool directed);
//
////释放邻接矩阵空间
//void Graph_EdgeSetList_Destroy(Graph_EdgeSet* graph);
////添加边(已存在时不添加)
//void Graph_EdgeSetList_Edge_Add(Graph_EdgeSet* graph, int no_origin, int no_destination, int weight);
//
//void Graph_EdgeSetList_Show(const Graph_EdgeSet& graph)
//{
//	std::cout << "顶点数：" << graph.num_vertex << std::endl
//		<< "边数：" << graph.num_edge << std::endl;
//	for (int i = 0; i < graph.num_vertex; i++)
//	{
//		printf("%d--<%d>--%d\n", graph.edge->top().no_source, graph.edge->top().weight, graph.edge->top().no_destination);
//		graph.edge->pop();
//	}
//}
//
///// 邻接矩阵转为边集数组存储
//Graph_EdgeSet* Graph_StorageConvert_EdgeSet(const Graph_matrix& graph)
//{
//	Graph_EdgeSet* g = new Graph_EdgeSet;
//	Graph_EdgeSetList_Init(g, graph.num_vertex, graph.directed);
//	int i = 0;
//	if (graph.directed == true)
//	{
//		for ( i ; i < graph.num_vertex; i++)
//		{
//			for (int c=i+1; c < graph.num_vertex; c++)
//			{
//				if (!CheckEdge_Infinit(graph.edge[i][c]))
//					Graph_EdgeSetList_Edge_Add(g, i, c, graph.edge[i][c]);
//			}
//		
//		}
//	}
//	else
//	{
//		for (i; i < graph.num_vertex; i++)
//		{
//			for (int c = 0; c < graph.num_vertex; c++)
//			{
//				if (!CheckEdge_Infinit(graph.edge[i][c]))
//					Graph_EdgeSetList_Edge_Add(g, i, c, graph.edge[i][c]);
//			}
//
//		}
//	}
//	return g;
//}













