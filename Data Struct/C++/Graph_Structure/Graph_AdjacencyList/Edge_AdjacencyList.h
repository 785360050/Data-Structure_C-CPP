#pragma once



struct Edge_AdjacencyList
{///邻接表的边(弧)
	int index_vertex;//顶点的下标索引
	int weight;//边权重
	Edge_AdjacencyList* next;
	Edge_AdjacencyList(int index, int weight)
		:index_vertex{ index }, weight{ weight }, next{ nullptr } {};
};