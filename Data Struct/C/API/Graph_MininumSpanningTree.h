#pragma once


#include "Graph_matrix.h"
#include "Tree_MergeFind_Set.h"


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






