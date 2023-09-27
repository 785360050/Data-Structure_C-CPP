#pragma once


#include "../API/Graph_matrix.h"
#include "../API/Tree_MergeFind_Set.h"


//求最小生成树,返回总权值	Kruskal
Graph_matrix* Graph_MininumSpanningTree_Kruskal(const Graph_matrix& graph)
{///TODO Unfinished
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
	Graph_Init(g, graph.num_vertex, graph.directed);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
	MFSet_QuickMerge* set_QM = Set_Create_QuickMerge(graph.num_vertex);
	//Set_Init(set_QM, set, graph.num_vertex);

	int a, b;
	for (int i = 0; i < graph.num_edge; i++)
	{
		//a=
	}

	Graph_Edge_Add(g, 0, 1, 1);
	Merge(set_QM, 0, 2);

	Set_Show(set_QM);

	std::cout << Find(set_QM, 0, 2) << std::endl;

	Set_Show(set_QM);
	std::cout << "RootIndex(2)= " << RootIndex(set_QM, 2) << std::endl;
	std::cout << "RootIndex(2)= " << RootIndex_Optimized(set_QM, 2) << std::endl;
	Set_Destroy(set_QM);
	return g;


}



Graph_matrix* Graph_MininumSpanningTree_Prim(const Graph_matrix& graph, int no_startvertex)
{
	int src = no_startvertex;
	int dst = 0;
	int totalcost = 0;
	bool* visited = new bool[graph.num_vertex];//标记是否已经加入生成树
	memset(visited, 0, sizeof(bool) * graph.num_vertex);
	int* cost = new int[graph.num_vertex];//标记最短路径的开销
	visited[no_startvertex] = true;
	int* path = new int[graph.num_vertex];//标记路径源点
	memset(path, 0, sizeof(int) * graph.num_vertex);

	Graph_matrix* g = new Graph_matrix;
	Graph_Init(g, graph.num_vertex, graph.directed);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)

	//初始化辅助记录表的信息
	for (int i = 0; i < graph.num_vertex; i++)
	{
		path[i] = 0;///空时为0
		if (visited[i] == false && !CheckEdge_Infinit(graph.edge[no_startvertex][i]))
		{///初始化起点的邻接距离
			cost[i] = graph.edge[src][i];
			path[i] = src;///初始化可达的源点
		}
		else
			cost[i] = 0;
	}
	
	//每一轮的Prim算法选择路径
	for (int round = 0; round < graph.num_vertex; round++)
	{
#ifdef info
		for (int i = 0; i < 7; i++)
			std::cout << cost[i] << '\t';
		std::cout << std::endl;
		for (int i = 0; i < 7; i++)
			std::cout << visited[i] << '\t';
		std::cout << std::endl;
		for (int i = 0; i < 7; i++)
			std::cout << path[i] << '\t';
		std::cout << std::endl << std::endl;
#endif // info

		int min = 1e4;
		for (int i = 0; i < graph.num_vertex; i++)
		{///遍历开销表找最小的点
			if (visited[i] == false && cost[i] > 0 && cost[i] < min )
			{///更新最小开销和目的顶点
				min = cost[i];
				dst = i;
			}
		}
		for (int i = 0; i < graph.num_vertex; i++)
		{///根据选中顶点更新开销表
			int c = graph.edge[dst][i];///路径开销
			bool e = !CheckEdge_Infinit(c);///边有效
			if (visited[i] == false && e && (c < cost[i] || cost[i] == 0))
			{///若到未访问的点开销比原来小，则更新开销和源点(或未被初始化时)
				cost[i] = c;
				path[i] = dst;
			}
		}
		visited[dst] = true;///找到最短路径并加入最小生成树
		Graph_Edge_Add(g, path[dst], dst, cost[dst]);
	}
	for (int i = 0; i < graph.num_vertex; i++)
		totalcost += cost[i];
	std::cout << "最小生成数的总权值为：" << totalcost << std::endl;
	delete[] visited;
	delete[] cost;
	delete[] path;
	return g;
}

