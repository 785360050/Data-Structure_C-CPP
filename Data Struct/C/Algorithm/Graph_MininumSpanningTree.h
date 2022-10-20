#pragma once


#include "../API/Graph_matrix.h"
#include "../API/Tree_MergeFind_Set.h"


//求最小生成树,返回总权值	Kruskal
Graph_matrix* Graph_MininumSpanningTree_Kruskal(Graph_matrix* graph, int* set, int n, int* result)
{
	/// <summary>
	/// Kruskal算法求最小生成树——相比Prim适合稀疏图
	/// 将任意存储方式转化为边集数组，方便边按权值排序
	/// 在动态生成最小生成树的时候，需要并查集辅助判断是否会形成环路
	/// 从小到大依次连上两个边，直到全部节点都连通，
	/// 若已经再并查集中，则不连(防止生成环)
	/// 将最终结果以边集数组的存储方式返回
	/// </summary>
	/// <param name="graph"></param>
	/// <param name="set"></param>
	/// <param name="sum"></param>
	/// <param name="result"></param>
	/// <returns></returns>

	Graph_matrix* g = new Graph_matrix;
	Graph_Init(g, 8, false);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
	MFSet_QuickMerge* set_QM = Set_Create_QuickMerge(n);
	Set_Init(set_QM, set, n);

	int a, b;
	for (int i = 0; i < graph->num_edge; i++)
	{
		a=
	}

	Graph_Edge_Add(g, 0, 1, 1);
	Merge(set_QM, 0, 2);

	Set_Show(set_QM);

	std::cout << Find(set_QM, 0, 2) << std::endl;

	Set_Show(set_QM);
	std::cout << "RootIndex(2)= " << RootIndex(set_QM, 2) << std::endl;
	std::cout << "RootIndex(2)= " << RootIndex_Optimized(set_QM, 2) << std::endl;
	Set_Destroy(set_QM);



}


//求最小生成树,返回新生成的图，邻接矩阵存储	Prim
Graph_matrix* Graph_MininumSpanningTree_Prim(Graph_matrix* graph,int num_vertex,int no_vertex)
{
	/// <summary>
	/// Prim算法求最小生成树，适合稠密图，以顶点为关键构造生成树
	/// 每次找到最小开销的顶点加入生成树，直到全部都加入为止
	/// </summary>
	static int inf = 0xffffffff;
	bool* visited = new bool[num_vertex];//标记是否已经加入生成树
	memset(visited, 0, sizeof(bool) * num_vertex);
	int* cost = new int[num_vertex];//标记最短路径的开销
	memset(visited, 0, sizeof(int) * num_vertex);
	int* path = new int[num_vertex];//标记路径源点
	memset(visited, 0, sizeof(int) * num_vertex);

	Graph_matrix* g = new Graph_matrix;
	Graph_Init(g, 8, false);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
	//for (int i = 0; i < graph->num_vertex; i++)
	//{
	//	cost[i] = graph->edge[no_vertex][i];//刷新路径开销
	//	visited[i] = 0;//？
	//	if (cost[i] > 0 && graph->edge[no_vertex][i] < cost[i])
	//		cost[i] = graph->edge[no_vertex][i];
	//}
	//visited[no_vertex] = true;//标记为已加入生成树
	//for (int i = 0; i < graph->num_vertex - 1; i++)
	//{
	//	for (int j = 0; j < graph->num_vertex; j++)
	//	{
	//		if(visited[j]==false&&cost[j]<)
	//	}
	//}
	
	visited[no_vertex] = true;//初始化起点的访问状态
	for (int i = 0; i < graph->num_vertex; i++)
	{//初始化路径开销表
		if (visited[i] == false&&CheckEdge_Infinit(graph->edge[no_vertex][i]))
		{//未访问且边存在时，初始化路径开销表
			cost[i] = graph->edge[no_vertex][i];
		}
	}

	for (int i = 0; i < graph->num_vertex; i++)
	{//找到最小开销
		int min = inf;
		for (int j = 0; j < graph->num_vertex; j++)
		{
			if (visited[j] == false && cost[j] < min)
			{
				min = cost[j];
				path[j] = j;
			}
			visited[j] = true;
			///更新最小生成树
			Graph_Edge_Add(g, j, i, min);
		}
		for (int j = 0;j < graph->num_vertex; j++)
		{
			if (visited[j] == false && graph->edge[path[j]][j] < cost[j])
			{
				cost[j] = graph->edge[path[j]][j];
				visited[j] = path[j];
			}
		}
	}
	return g;



}


