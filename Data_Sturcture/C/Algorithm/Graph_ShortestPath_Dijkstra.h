#pragma once



#include "../API/Graph_matrix.h"








#include <stack>
//单源最短路径	Dijkstra
//void ShortestPath_Dijkstra(const Graph_matrix& graph, int no_start)
//{
//	static int INF = 0xffffffff;
//	bool* visited = new bool[graph.num_vertex];//记录激活状态
//	int* distance = new int[graph.num_vertex];//记录当前最短距离
//	int* path_pre = new int[graph.num_vertex];//记录历史路径(上一个经过的路径)
//
//	Graph_matrix* g = new Graph_matrix;
//
//	///初始化路径长度、访问激活状态、路径记录
//	for (int i = 0; i < graph.num_vertex; i++)
//	{
//		distance[i] = graph.edge[no_start][i];
//		visited[i] = false;//初始化为未激活状态
//		path_pre[i] = graph.edge[no_start][i] < INF ? no_start : -1;
//	}
//	visited[no_start] = true;
//	distance[no_start] = 0;
//	path_pre[no_start] = -1;
//
//	int min = INF;
//	static int temp;
//	///循环更新各表，找到最短路径
//	for (int i = 0; i < graph.num_vertex - 1; i++)
//	{
//		for(int j=0;j<graph.num_vertex;j++)
//			///找到当前最短的距离和顶点
//			if (visited[j] == false && distance[j] < min)
//			{
//				min = distance[j];
//				temp = j;
//			}
//		visited[temp] = true;
//		for (int j = 0; j < graph.num_vertex; j++)
//		{///更新最短路径距离表和路径历史表
//			if (visited[j] == false && path_pre[temp] + graph.edge[temp][i] < distance[j])
//			{
//				distance[j] = distance[temp] + graph.edge[temp][j];
//				path_pre[j] = temp;
//			}
//		}
//
//	}
//	//未完成路径处理
//	for (int i = 0; i < graph.num_vertex; i++)
//		std::cout << path_pre[i] << ' ';
//
//	Graph_Show_Matrix(g);
//}

void ShortestPath_Dijkstra(const Graph_matrix& graph, int no_start)
{
	static int INF = 0xffffffff;
	bool* visited = new bool[graph.num_vertex];//记录激活状态
	int* path_pre = new int[graph.num_vertex];//记录历史路径(上一个经过的路径)

	Graph_matrix* g = new Graph_matrix;///新建一个邻接矩阵存放最小路径
	Graph_Init(g, graph.num_vertex, graph.directed);

	///初始化访问激活状态、路径记录
	for (int i = 0; i < graph.num_vertex; i++)
	{
		visited[i] = false;//初始化为未激活状态
		path_pre[i] = graph.edge[no_start][i] < INF ? no_start : -1;//可能有bug
	}
	visited[no_start] = true;
	path_pre[no_start] = -1;

	int min = INF;
	static int temp;
	///循环更新各表，找到最短路径
	for (int i = 0; i < graph.num_vertex - 1; i++)
	{
		for (int j = 0; j < graph.num_vertex; j++)
			///找到当前最短的距离和顶点
			if (visited[j] == false && graph.edge[i][j] < min)
			{
				min = graph.edge[i][j];
				temp = j;
			}
		visited[temp] = true;
		for (int j = 0; j < graph.num_vertex; j++)
		{///更新最短路径距离表和路径历史表
			if (visited[j] == false && path_pre[temp] + graph.edge[temp][i] < graph.edge[i][j])
			{
				graph.edge[i][j] = graph.edge[i][temp] + graph.edge[temp][j];
				path_pre[j] = temp;
			}
		}

	}
	//未完成路径处理
	for (int i = 0; i < graph.num_vertex; i++)
		std::cout << path_pre[i] << ' ';

	Graph_Show_Matrix(g);
}

















