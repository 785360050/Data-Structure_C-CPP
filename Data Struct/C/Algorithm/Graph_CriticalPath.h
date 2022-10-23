#pragma once


#include <iostream>

#include <stack>
#include "../API/Liner_Stack.h"
#include "Graph_TopoSort.h"
#include "../API/Graph_AdjacencyList.h"

// 适用于关键路径的拓扑排序，在基础拓扑排序的基础上做了部分改动，排序时更新顶点最早发生时间表
static std::stack<int>* TopoSort_ForCriticalPath(AdjacencyList* graph,int* vertext_earliest,int num_array)
{
	std::stack<int> s;	//缓存入度为0的点，用队列也行
	std::stack<int>* toporesult = new std::stack<int>;//用栈存放拓扑排序结果
	int* indegree = new int[graph->num_vertex];//记录入度
	memset(indegree, 0, sizeof(int) * graph->num_vertex);
	for (int i = 0; i < graph->num_vertex; i++)
	{//初始化入度表
		if (graph->vertex[i].head_edge)
		{
			AdjacencyList_Edge* temp = graph->vertex[i].head_edge;
			while (temp)
			{///跟新一个顶点的入度总和
				indegree[temp->index_vertex]++;
				temp = temp->next;
			}
		}
	}

	for (int i = 0; i < graph->num_vertex; i++)
		if (indegree[i] == 0)///遍历入度表，将入度为0的顶点入栈缓存
			s.push(i);

	int no;
	int count = 0;///统计拓扑排序结果顶点数，不等于图顶点数时表明有环
	while (!s.empty())
	{///复制一个栈，保留原有栈用于关键路径更新顶点最早发生时间
		no = s.top();
		toporesult->push(no);
		s.pop();
		std::cout << no << ' ';///以输出方式显示拓扑排序结果
		count++;
		AdjacencyList_Edge* temp = graph->vertex[no].head_edge;
		while (temp)
		{///遍历已访问的顶点的邻接表，出现的顶点入度-1，更新后后若为0，则入栈缓存
			indegree[temp->index_vertex]--;
			if (indegree[temp->index_vertex] == 0)
				s.push(temp->index_vertex);
			if (vertext_earliest[no] + temp->weight > vertext_earliest[temp->index_vertex])
			{///更新顶点最早开始时间——————————————————关键路径改动功能
				vertext_earliest[temp->index_vertex] = vertext_earliest[no] + temp->weight;
			}
			temp = temp->next;
		}
	}
	delete[] indegree;
	if (count == graph->num_vertex)
	{
		//std::cout << "Topo Sort Succeeded" << std::endl;
		//while (!toporesult->empty())
		//{
		//	std::cout << toporesult->top() << ' ';
		//	toporesult->pop();
		//}
		std::cout << std::endl;
		return toporesult;
	}
	else
	{
		std::cout << "Topo Sort Faild: Cycle exisit" << std::endl;
	}
}

bool Graph_CriticalPath(AdjacencyList* graph)
{///Using Standard Stack
	try
	{///无环时才能计算关键路径
		if (!TopoSort(graph))
			throw 1;
	}
	catch (...)
	{
		std::cout << "Critical Path is not exsist: Cycle Exsisted in Graph" << std::endl;
		return false;
	}
	int* vertex_e = new int[graph->num_vertex];//earliest time of vertex
	memset(vertex_e, 0, sizeof(int) * graph->num_vertex);
	int* vertex_l = new int[graph->num_vertex];//latest time of vertex
	memset(vertex_l, 0, sizeof(int) * graph->num_vertex);
	std::stack<int>* s = TopoSort_ForCriticalPath(graph, vertex_e, graph->num_vertex);
	//std::cout << "Topo Sort Succeeded" << std::endl;
	//	while (!s->empty())
	//	{
	//		std::cout << s->top() << ' ';
	//		s->pop();
	//	}
	for (int i = 0; i < graph->num_vertex; i++)
	{///初始化最晚发生时间表,全部设为最晚值
		vertex_l[i] = vertex_e[graph->num_vertex - 1];
	}
	//for (int i = 0; i < graph->num_vertex; i++)
	//	printf("%d ", vertex_e[i]);
	//printf("\n");
	//for (int i = 0; i < graph->num_vertex; i++)
	//	printf("%d ", vertex_l[i]);
	while (!s->empty())
	{///更新顶点最晚发生时间表
		int no = s->top(); s->pop();
		AdjacencyList_Edge* e = graph->vertex[no].head_edge;
		while (e)
		{///从后往前更新最晚时间，
			if (vertex_l[e->index_vertex] - e->weight < vertex_l[no])
				vertex_l[no] = vertex_l[e->index_vertex] - e->weight;
			e = e->next;
		}
	}
	//printf("\n");
	//for (int i = 0; i < graph->num_vertex; i++)
	//	printf("%d ", vertex_e[i]);
	//printf("\n");
	//for (int i = 0; i < graph->num_vertex; i++)
	//	printf("%d ", vertex_l[i]);
	std::cout << "所有关键的边为：" << std::endl;
	for (int i = 0; i < graph->num_vertex; i++)
	{///求关键路径
		AdjacencyList_Edge* e = graph->vertex[i].head_edge;
		while (e)
		{///若活动(边)的 最晚发生时间=最早发生时间 则判断为关键路径（关键路径不唯一）
			int edge_EarliestTime = vertex_e[i];///活动的最早发生时间
			int edge_LatestTime = vertex_l[e->index_vertex] - e->weight;///活动的最晚发生时间
			if (edge_EarliestTime == edge_LatestTime)
				printf("%d--<%d>--%d\n",
					graph->vertex[i].no,
					e->weight,
					graph->vertex[e->index_vertex].no);
			e = e->next;
		}

	}
	return true;
}






